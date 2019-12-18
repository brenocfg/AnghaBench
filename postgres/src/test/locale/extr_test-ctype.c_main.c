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
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  describe_char (short) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int
main()
{
	short		c;
	char	   *cur_locale;

	cur_locale = setlocale(LC_ALL, "");
	if (cur_locale)
		fprintf(stderr, "Successfully set locale to \"%s\"\n", cur_locale);
	else
	{
		fprintf(stderr, "Cannot setup locale. Either your libc does not provide\nlocale support, or your locale data is corrupt, or you have not set\nLANG or LC_CTYPE environment variable to proper value. Program aborted.\n");
		return 1;
	}

	printf("char#  char alnum alpha cntrl digit lower graph print punct space upper xdigit lo up\n");
	for (c = 0; c <= 255; c++)
		describe_char(c);

	return 0;
}