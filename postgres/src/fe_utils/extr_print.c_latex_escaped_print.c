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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputc (char const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
latex_escaped_print(const char *in, FILE *fout)
{
	const char *p;

	for (p = in; *p; p++)
		switch (*p)
		{
				/*
				 * We convert ASCII characters per the recommendations in
				 * Scott Pakin's "The Comprehensive LATEX Symbol List",
				 * available from CTAN.  For non-ASCII, you're on your own.
				 */
			case '#':
				fputs("\\#", fout);
				break;
			case '$':
				fputs("\\$", fout);
				break;
			case '%':
				fputs("\\%", fout);
				break;
			case '&':
				fputs("\\&", fout);
				break;
			case '<':
				fputs("\\textless{}", fout);
				break;
			case '>':
				fputs("\\textgreater{}", fout);
				break;
			case '\\':
				fputs("\\textbackslash{}", fout);
				break;
			case '^':
				fputs("\\^{}", fout);
				break;
			case '_':
				fputs("\\_", fout);
				break;
			case '{':
				fputs("\\{", fout);
				break;
			case '|':
				fputs("\\textbar{}", fout);
				break;
			case '}':
				fputs("\\}", fout);
				break;
			case '~':
				fputs("\\~{}", fout);
				break;
			case '\n':
				/* This is not right, but doing it right seems too hard */
				fputs("\\\\", fout);
				break;
			default:
				fputc(*p, fout);
		}
}