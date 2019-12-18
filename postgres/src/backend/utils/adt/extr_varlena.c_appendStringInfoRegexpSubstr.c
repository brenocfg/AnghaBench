#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_3__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int charlen_to_bytelen (char*,int) ; 
 int pg_database_encoding_max_length () ; 
 int /*<<< orphan*/  pg_mblen (char const*) ; 

__attribute__((used)) static void
appendStringInfoRegexpSubstr(StringInfo str, text *replace_text,
							 regmatch_t *pmatch,
							 char *start_ptr, int data_pos)
{
	const char *p = VARDATA_ANY(replace_text);
	const char *p_end = p + VARSIZE_ANY_EXHDR(replace_text);
	int			eml = pg_database_encoding_max_length();

	for (;;)
	{
		const char *chunk_start = p;
		int			so;
		int			eo;

		/* Find next escape char. */
		if (eml == 1)
		{
			for (; p < p_end && *p != '\\'; p++)
				 /* nothing */ ;
		}
		else
		{
			for (; p < p_end && *p != '\\'; p += pg_mblen(p))
				 /* nothing */ ;
		}

		/* Copy the text we just scanned over, if any. */
		if (p > chunk_start)
			appendBinaryStringInfo(str, chunk_start, p - chunk_start);

		/* Done if at end of string, else advance over escape char. */
		if (p >= p_end)
			break;
		p++;

		if (p >= p_end)
		{
			/* Escape at very end of input.  Treat same as unexpected char */
			appendStringInfoChar(str, '\\');
			break;
		}

		if (*p >= '1' && *p <= '9')
		{
			/* Use the back reference of regexp. */
			int			idx = *p - '0';

			so = pmatch[idx].rm_so;
			eo = pmatch[idx].rm_eo;
			p++;
		}
		else if (*p == '&')
		{
			/* Use the entire matched string. */
			so = pmatch[0].rm_so;
			eo = pmatch[0].rm_eo;
			p++;
		}
		else if (*p == '\\')
		{
			/* \\ means transfer one \ to output. */
			appendStringInfoChar(str, '\\');
			p++;
			continue;
		}
		else
		{
			/*
			 * If escape char is not followed by any expected char, just treat
			 * it as ordinary data to copy.  (XXX would it be better to throw
			 * an error?)
			 */
			appendStringInfoChar(str, '\\');
			continue;
		}

		if (so != -1 && eo != -1)
		{
			/*
			 * Copy the text that is back reference of regexp.  Note so and eo
			 * are counted in characters not bytes.
			 */
			char	   *chunk_start;
			int			chunk_len;

			Assert(so >= data_pos);
			chunk_start = start_ptr;
			chunk_start += charlen_to_bytelen(chunk_start, so - data_pos);
			chunk_len = charlen_to_bytelen(chunk_start, eo - so);
			appendBinaryStringInfo(str, chunk_start, chunk_len);
		}
	}
}