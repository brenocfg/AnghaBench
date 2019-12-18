#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  base_yyout ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
output_escaped_str(char *str, bool quoted)
{
	int			i = 0;
	int			len = strlen(str);

	if (quoted && str[0] == '"' && str[len - 1] == '"') /* do not escape quotes
														 * at beginning and end
														 * if quoted string */
	{
		i = 1;
		len--;
		fputs("\"", base_yyout);
	}

	/* output this char by char as we have to filter " and \n */
	for (; i < len; i++)
	{
		if (str[i] == '"')
			fputs("\\\"", base_yyout);
		else if (str[i] == '\n')
			fputs("\\\n", base_yyout);
		else if (str[i] == '\\')
		{
			int			j = i;

			/*
			 * check whether this is a continuation line if it is, do not
			 * output anything because newlines are escaped anyway
			 */

			/* accept blanks after the '\' as some other compilers do too */
			do
			{
				j++;
			} while (str[j] == ' ' || str[j] == '\t');

			if ((str[j] != '\n') && (str[j] != '\r' || str[j + 1] != '\n')) /* not followed by a
																			 * newline */
				fputs("\\\\", base_yyout);
		}
		else if (str[i] == '\r' && str[i + 1] == '\n')
		{
			fputs("\\\r\n", base_yyout);
			i++;
		}
		else
			fputc(str[i], base_yyout);
	}

	if (quoted && str[0] == '"' && str[len] == '"')
		fputs("\"", base_yyout);
}