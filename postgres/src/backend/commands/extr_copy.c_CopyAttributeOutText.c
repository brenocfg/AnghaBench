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
struct TYPE_4__ {char* delim; int /*<<< orphan*/  file_encoding; scalar_t__ encoding_embeds_ascii; scalar_t__ need_transcoding; } ;
typedef  TYPE_1__* CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  CopySendChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  DUMPSOFAR () ; 
 scalar_t__ IS_HIGHBIT_SET (char) ; 
 int /*<<< orphan*/  pg_encoding_mblen (int /*<<< orphan*/ ,char*) ; 
 char* pg_server_to_any (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
CopyAttributeOutText(CopyState cstate, char *string)
{
	char	   *ptr;
	char	   *start;
	char		c;
	char		delimc = cstate->delim[0];

	if (cstate->need_transcoding)
		ptr = pg_server_to_any(string, strlen(string), cstate->file_encoding);
	else
		ptr = string;

	/*
	 * We have to grovel through the string searching for control characters
	 * and instances of the delimiter character.  In most cases, though, these
	 * are infrequent.  To avoid overhead from calling CopySendData once per
	 * character, we dump out all characters between escaped characters in a
	 * single call.  The loop invariant is that the data from "start" to "ptr"
	 * can be sent literally, but hasn't yet been.
	 *
	 * We can skip pg_encoding_mblen() overhead when encoding is safe, because
	 * in valid backend encodings, extra bytes of a multibyte character never
	 * look like ASCII.  This loop is sufficiently performance-critical that
	 * it's worth making two copies of it to get the IS_HIGHBIT_SET() test out
	 * of the normal safe-encoding path.
	 */
	if (cstate->encoding_embeds_ascii)
	{
		start = ptr;
		while ((c = *ptr) != '\0')
		{
			if ((unsigned char) c < (unsigned char) 0x20)
			{
				/*
				 * \r and \n must be escaped, the others are traditional. We
				 * prefer to dump these using the C-like notation, rather than
				 * a backslash and the literal character, because it makes the
				 * dump file a bit more proof against Microsoftish data
				 * mangling.
				 */
				switch (c)
				{
					case '\b':
						c = 'b';
						break;
					case '\f':
						c = 'f';
						break;
					case '\n':
						c = 'n';
						break;
					case '\r':
						c = 'r';
						break;
					case '\t':
						c = 't';
						break;
					case '\v':
						c = 'v';
						break;
					default:
						/* If it's the delimiter, must backslash it */
						if (c == delimc)
							break;
						/* All ASCII control chars are length 1 */
						ptr++;
						continue;	/* fall to end of loop */
				}
				/* if we get here, we need to convert the control char */
				DUMPSOFAR();
				CopySendChar(cstate, '\\');
				CopySendChar(cstate, c);
				start = ++ptr;	/* do not include char in next run */
			}
			else if (c == '\\' || c == delimc)
			{
				DUMPSOFAR();
				CopySendChar(cstate, '\\');
				start = ptr++;	/* we include char in next run */
			}
			else if (IS_HIGHBIT_SET(c))
				ptr += pg_encoding_mblen(cstate->file_encoding, ptr);
			else
				ptr++;
		}
	}
	else
	{
		start = ptr;
		while ((c = *ptr) != '\0')
		{
			if ((unsigned char) c < (unsigned char) 0x20)
			{
				/*
				 * \r and \n must be escaped, the others are traditional. We
				 * prefer to dump these using the C-like notation, rather than
				 * a backslash and the literal character, because it makes the
				 * dump file a bit more proof against Microsoftish data
				 * mangling.
				 */
				switch (c)
				{
					case '\b':
						c = 'b';
						break;
					case '\f':
						c = 'f';
						break;
					case '\n':
						c = 'n';
						break;
					case '\r':
						c = 'r';
						break;
					case '\t':
						c = 't';
						break;
					case '\v':
						c = 'v';
						break;
					default:
						/* If it's the delimiter, must backslash it */
						if (c == delimc)
							break;
						/* All ASCII control chars are length 1 */
						ptr++;
						continue;	/* fall to end of loop */
				}
				/* if we get here, we need to convert the control char */
				DUMPSOFAR();
				CopySendChar(cstate, '\\');
				CopySendChar(cstate, c);
				start = ++ptr;	/* do not include char in next run */
			}
			else if (c == '\\' || c == delimc)
			{
				DUMPSOFAR();
				CopySendChar(cstate, '\\');
				start = ptr++;	/* we include char in next run */
			}
			else
				ptr++;
		}
	}

	DUMPSOFAR();
}