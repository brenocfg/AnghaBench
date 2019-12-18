#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* delim; char* quote; char* escape; char* null_print; int /*<<< orphan*/  file_encoding; scalar_t__ encoding_embeds_ascii; scalar_t__ need_transcoding; } ;
typedef  TYPE_1__* CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  CopySendChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  CopySendString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  DUMPSOFAR () ; 
 scalar_t__ IS_HIGHBIT_SET (char) ; 
 int /*<<< orphan*/  pg_encoding_mblen (int /*<<< orphan*/ ,char*) ; 
 char* pg_server_to_any (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
CopyAttributeOutCSV(CopyState cstate, char *string,
					bool use_quote, bool single_attr)
{
	char	   *ptr;
	char	   *start;
	char		c;
	char		delimc = cstate->delim[0];
	char		quotec = cstate->quote[0];
	char		escapec = cstate->escape[0];

	/* force quoting if it matches null_print (before conversion!) */
	if (!use_quote && strcmp(string, cstate->null_print) == 0)
		use_quote = true;

	if (cstate->need_transcoding)
		ptr = pg_server_to_any(string, strlen(string), cstate->file_encoding);
	else
		ptr = string;

	/*
	 * Make a preliminary pass to discover if it needs quoting
	 */
	if (!use_quote)
	{
		/*
		 * Because '\.' can be a data value, quote it if it appears alone on a
		 * line so it is not interpreted as the end-of-data marker.
		 */
		if (single_attr && strcmp(ptr, "\\.") == 0)
			use_quote = true;
		else
		{
			char	   *tptr = ptr;

			while ((c = *tptr) != '\0')
			{
				if (c == delimc || c == quotec || c == '\n' || c == '\r')
				{
					use_quote = true;
					break;
				}
				if (IS_HIGHBIT_SET(c) && cstate->encoding_embeds_ascii)
					tptr += pg_encoding_mblen(cstate->file_encoding, tptr);
				else
					tptr++;
			}
		}
	}

	if (use_quote)
	{
		CopySendChar(cstate, quotec);

		/*
		 * We adopt the same optimization strategy as in CopyAttributeOutText
		 */
		start = ptr;
		while ((c = *ptr) != '\0')
		{
			if (c == quotec || c == escapec)
			{
				DUMPSOFAR();
				CopySendChar(cstate, escapec);
				start = ptr;	/* we include char in next run */
			}
			if (IS_HIGHBIT_SET(c) && cstate->encoding_embeds_ascii)
				ptr += pg_encoding_mblen(cstate->file_encoding, ptr);
			else
				ptr++;
		}
		DUMPSOFAR();

		CopySendChar(cstate, quotec);
	}
	else
	{
		/* If it doesn't need quoting, we can just dump it as-is */
		CopySendString(cstate, ptr);
	}
}