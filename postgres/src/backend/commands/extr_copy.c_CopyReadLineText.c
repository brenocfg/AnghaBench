#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* quote; char* escape; char* raw_buf; int raw_buf_index; int raw_buf_len; scalar_t__ eol_type; int /*<<< orphan*/  file_encoding; scalar_t__ encoding_embeds_ascii; scalar_t__ csv_mode; int /*<<< orphan*/  line_buf; int /*<<< orphan*/  cur_lineno; } ;
typedef  TYPE_1__* CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  CopyLoadRawBuf (TYPE_1__*) ; 
 scalar_t__ EOL_CR ; 
 scalar_t__ EOL_CRNL ; 
 scalar_t__ EOL_NL ; 
 scalar_t__ EOL_UNKNOWN ; 
 int /*<<< orphan*/  ERRCODE_BAD_COPY_FILE_FORMAT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IF_NEED_REFILL_AND_EOF_BREAK (int) ; 
 int /*<<< orphan*/  IF_NEED_REFILL_AND_NOT_EOF_CONTINUE (int) ; 
 scalar_t__ IS_HIGHBIT_SET (char) ; 
 int /*<<< orphan*/  NO_END_OF_COPY_GOTO ; 
 int /*<<< orphan*/  REFILL_LINEBUF ; 
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int pg_encoding_mblen (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
CopyReadLineText(CopyState cstate)
{
	char	   *copy_raw_buf;
	int			raw_buf_ptr;
	int			copy_buf_len;
	bool		need_data = false;
	bool		hit_eof = false;
	bool		result = false;
	char		mblen_str[2];

	/* CSV variables */
	bool		first_char_in_line = true;
	bool		in_quote = false,
				last_was_esc = false;
	char		quotec = '\0';
	char		escapec = '\0';

	if (cstate->csv_mode)
	{
		quotec = cstate->quote[0];
		escapec = cstate->escape[0];
		/* ignore special escape processing if it's the same as quotec */
		if (quotec == escapec)
			escapec = '\0';
	}

	mblen_str[1] = '\0';

	/*
	 * The objective of this loop is to transfer the entire next input line
	 * into line_buf.  Hence, we only care for detecting newlines (\r and/or
	 * \n) and the end-of-copy marker (\.).
	 *
	 * In CSV mode, \r and \n inside a quoted field are just part of the data
	 * value and are put in line_buf.  We keep just enough state to know if we
	 * are currently in a quoted field or not.
	 *
	 * These four characters, and the CSV escape and quote characters, are
	 * assumed the same in frontend and backend encodings.
	 *
	 * For speed, we try to move data from raw_buf to line_buf in chunks
	 * rather than one character at a time.  raw_buf_ptr points to the next
	 * character to examine; any characters from raw_buf_index to raw_buf_ptr
	 * have been determined to be part of the line, but not yet transferred to
	 * line_buf.
	 *
	 * For a little extra speed within the loop, we copy raw_buf and
	 * raw_buf_len into local variables.
	 */
	copy_raw_buf = cstate->raw_buf;
	raw_buf_ptr = cstate->raw_buf_index;
	copy_buf_len = cstate->raw_buf_len;

	for (;;)
	{
		int			prev_raw_ptr;
		char		c;

		/*
		 * Load more data if needed.  Ideally we would just force four bytes
		 * of read-ahead and avoid the many calls to
		 * IF_NEED_REFILL_AND_NOT_EOF_CONTINUE(), but the COPY_OLD_FE protocol
		 * does not allow us to read too far ahead or we might read into the
		 * next data, so we read-ahead only as far we know we can.  One
		 * optimization would be to read-ahead four byte here if
		 * cstate->copy_dest != COPY_OLD_FE, but it hardly seems worth it,
		 * considering the size of the buffer.
		 */
		if (raw_buf_ptr >= copy_buf_len || need_data)
		{
			REFILL_LINEBUF;

			/*
			 * Try to read some more data.  This will certainly reset
			 * raw_buf_index to zero, and raw_buf_ptr must go with it.
			 */
			if (!CopyLoadRawBuf(cstate))
				hit_eof = true;
			raw_buf_ptr = 0;
			copy_buf_len = cstate->raw_buf_len;

			/*
			 * If we are completely out of data, break out of the loop,
			 * reporting EOF.
			 */
			if (copy_buf_len <= 0)
			{
				result = true;
				break;
			}
			need_data = false;
		}

		/* OK to fetch a character */
		prev_raw_ptr = raw_buf_ptr;
		c = copy_raw_buf[raw_buf_ptr++];

		if (cstate->csv_mode)
		{
			/*
			 * If character is '\\' or '\r', we may need to look ahead below.
			 * Force fetch of the next character if we don't already have it.
			 * We need to do this before changing CSV state, in case one of
			 * these characters is also the quote or escape character.
			 *
			 * Note: old-protocol does not like forced prefetch, but it's OK
			 * here since we cannot validly be at EOF.
			 */
			if (c == '\\' || c == '\r')
			{
				IF_NEED_REFILL_AND_NOT_EOF_CONTINUE(0);
			}

			/*
			 * Dealing with quotes and escapes here is mildly tricky. If the
			 * quote char is also the escape char, there's no problem - we
			 * just use the char as a toggle. If they are different, we need
			 * to ensure that we only take account of an escape inside a
			 * quoted field and immediately preceding a quote char, and not
			 * the second in an escape-escape sequence.
			 */
			if (in_quote && c == escapec)
				last_was_esc = !last_was_esc;
			if (c == quotec && !last_was_esc)
				in_quote = !in_quote;
			if (c != escapec)
				last_was_esc = false;

			/*
			 * Updating the line count for embedded CR and/or LF chars is
			 * necessarily a little fragile - this test is probably about the
			 * best we can do.  (XXX it's arguable whether we should do this
			 * at all --- is cur_lineno a physical or logical count?)
			 */
			if (in_quote && c == (cstate->eol_type == EOL_NL ? '\n' : '\r'))
				cstate->cur_lineno++;
		}

		/* Process \r */
		if (c == '\r' && (!cstate->csv_mode || !in_quote))
		{
			/* Check for \r\n on first line, _and_ handle \r\n. */
			if (cstate->eol_type == EOL_UNKNOWN ||
				cstate->eol_type == EOL_CRNL)
			{
				/*
				 * If need more data, go back to loop top to load it.
				 *
				 * Note that if we are at EOF, c will wind up as '\0' because
				 * of the guaranteed pad of raw_buf.
				 */
				IF_NEED_REFILL_AND_NOT_EOF_CONTINUE(0);

				/* get next char */
				c = copy_raw_buf[raw_buf_ptr];

				if (c == '\n')
				{
					raw_buf_ptr++;	/* eat newline */
					cstate->eol_type = EOL_CRNL;	/* in case not set yet */
				}
				else
				{
					/* found \r, but no \n */
					if (cstate->eol_type == EOL_CRNL)
						ereport(ERROR,
								(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
								 !cstate->csv_mode ?
								 errmsg("literal carriage return found in data") :
								 errmsg("unquoted carriage return found in data"),
								 !cstate->csv_mode ?
								 errhint("Use \"\\r\" to represent carriage return.") :
								 errhint("Use quoted CSV field to represent carriage return.")));

					/*
					 * if we got here, it is the first line and we didn't find
					 * \n, so don't consume the peeked character
					 */
					cstate->eol_type = EOL_CR;
				}
			}
			else if (cstate->eol_type == EOL_NL)
				ereport(ERROR,
						(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
						 !cstate->csv_mode ?
						 errmsg("literal carriage return found in data") :
						 errmsg("unquoted carriage return found in data"),
						 !cstate->csv_mode ?
						 errhint("Use \"\\r\" to represent carriage return.") :
						 errhint("Use quoted CSV field to represent carriage return.")));
			/* If reach here, we have found the line terminator */
			break;
		}

		/* Process \n */
		if (c == '\n' && (!cstate->csv_mode || !in_quote))
		{
			if (cstate->eol_type == EOL_CR || cstate->eol_type == EOL_CRNL)
				ereport(ERROR,
						(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
						 !cstate->csv_mode ?
						 errmsg("literal newline found in data") :
						 errmsg("unquoted newline found in data"),
						 !cstate->csv_mode ?
						 errhint("Use \"\\n\" to represent newline.") :
						 errhint("Use quoted CSV field to represent newline.")));
			cstate->eol_type = EOL_NL;	/* in case not set yet */
			/* If reach here, we have found the line terminator */
			break;
		}

		/*
		 * In CSV mode, we only recognize \. alone on a line.  This is because
		 * \. is a valid CSV data value.
		 */
		if (c == '\\' && (!cstate->csv_mode || first_char_in_line))
		{
			char		c2;

			IF_NEED_REFILL_AND_NOT_EOF_CONTINUE(0);
			IF_NEED_REFILL_AND_EOF_BREAK(0);

			/* -----
			 * get next character
			 * Note: we do not change c so if it isn't \., we can fall
			 * through and continue processing for file encoding.
			 * -----
			 */
			c2 = copy_raw_buf[raw_buf_ptr];

			if (c2 == '.')
			{
				raw_buf_ptr++;	/* consume the '.' */

				/*
				 * Note: if we loop back for more data here, it does not
				 * matter that the CSV state change checks are re-executed; we
				 * will come back here with no important state changed.
				 */
				if (cstate->eol_type == EOL_CRNL)
				{
					/* Get the next character */
					IF_NEED_REFILL_AND_NOT_EOF_CONTINUE(0);
					/* if hit_eof, c2 will become '\0' */
					c2 = copy_raw_buf[raw_buf_ptr++];

					if (c2 == '\n')
					{
						if (!cstate->csv_mode)
							ereport(ERROR,
									(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
									 errmsg("end-of-copy marker does not match previous newline style")));
						else
							NO_END_OF_COPY_GOTO;
					}
					else if (c2 != '\r')
					{
						if (!cstate->csv_mode)
							ereport(ERROR,
									(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
									 errmsg("end-of-copy marker corrupt")));
						else
							NO_END_OF_COPY_GOTO;
					}
				}

				/* Get the next character */
				IF_NEED_REFILL_AND_NOT_EOF_CONTINUE(0);
				/* if hit_eof, c2 will become '\0' */
				c2 = copy_raw_buf[raw_buf_ptr++];

				if (c2 != '\r' && c2 != '\n')
				{
					if (!cstate->csv_mode)
						ereport(ERROR,
								(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
								 errmsg("end-of-copy marker corrupt")));
					else
						NO_END_OF_COPY_GOTO;
				}

				if ((cstate->eol_type == EOL_NL && c2 != '\n') ||
					(cstate->eol_type == EOL_CRNL && c2 != '\n') ||
					(cstate->eol_type == EOL_CR && c2 != '\r'))
				{
					ereport(ERROR,
							(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
							 errmsg("end-of-copy marker does not match previous newline style")));
				}

				/*
				 * Transfer only the data before the \. into line_buf, then
				 * discard the data and the \. sequence.
				 */
				if (prev_raw_ptr > cstate->raw_buf_index)
					appendBinaryStringInfo(&cstate->line_buf,
										   cstate->raw_buf + cstate->raw_buf_index,
										   prev_raw_ptr - cstate->raw_buf_index);
				cstate->raw_buf_index = raw_buf_ptr;
				result = true;	/* report EOF */
				break;
			}
			else if (!cstate->csv_mode)

				/*
				 * If we are here, it means we found a backslash followed by
				 * something other than a period.  In non-CSV mode, anything
				 * after a backslash is special, so we skip over that second
				 * character too.  If we didn't do that \\. would be
				 * considered an eof-of copy, while in non-CSV mode it is a
				 * literal backslash followed by a period.  In CSV mode,
				 * backslashes are not special, so we want to process the
				 * character after the backslash just like a normal character,
				 * so we don't increment in those cases.
				 */
				raw_buf_ptr++;
		}

		/*
		 * This label is for CSV cases where \. appears at the start of a
		 * line, but there is more text after it, meaning it was a data value.
		 * We are more strict for \. in CSV mode because \. could be a data
		 * value, while in non-CSV mode, \. cannot be a data value.
		 */
not_end_of_copy:

		/*
		 * Process all bytes of a multi-byte character as a group.
		 *
		 * We only support multi-byte sequences where the first byte has the
		 * high-bit set, so as an optimization we can avoid this block
		 * entirely if it is not set.
		 */
		if (cstate->encoding_embeds_ascii && IS_HIGHBIT_SET(c))
		{
			int			mblen;

			/*
			 * It is enough to look at the first byte in all our encodings, to
			 * get the length.  (GB18030 is a bit special, but still works for
			 * our purposes; see comment in pg_gb18030_mblen())
			 */
			mblen_str[0] = c;
			mblen = pg_encoding_mblen(cstate->file_encoding, mblen_str);

			IF_NEED_REFILL_AND_NOT_EOF_CONTINUE(mblen - 1);
			IF_NEED_REFILL_AND_EOF_BREAK(mblen - 1);
			raw_buf_ptr += mblen - 1;
		}
		first_char_in_line = false;
	}							/* end of outer loop */

	/*
	 * Transfer any still-uncopied data to line_buf.
	 */
	REFILL_LINEBUF;

	return result;
}