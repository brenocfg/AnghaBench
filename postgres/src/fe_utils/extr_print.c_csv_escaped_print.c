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

__attribute__((used)) static void
csv_escaped_print(const char *str, FILE *fout)
{
	const char *p;

	fputc('"', fout);
	for (p = str; *p; p++)
	{
		if (*p == '"')
			fputc('"', fout);	/* double quotes are doubled */
		fputc(*p, fout);
	}
	fputc('"', fout);
}