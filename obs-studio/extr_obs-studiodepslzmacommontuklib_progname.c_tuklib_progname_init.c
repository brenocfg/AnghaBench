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
 char* progname ; 

extern void
tuklib_progname_init(char **argv)
{
#ifdef TUKLIB_DOSLIKE
	// On these systems, argv[0] always has the full path and .exe
	// suffix even if the user just types the plain program name.
	// We modify argv[0] to make it nicer to read.

	// Strip the leading path.
	char *p = argv[0] + strlen(argv[0]);
	while (argv[0] < p && p[-1] != '/' && p[-1] != '\\')
		--p;

	argv[0] = p;

	// Strip the .exe suffix.
	p = strrchr(p, '.');
	if (p != NULL)
		*p = '\0';

	// Make it lowercase.
	for (p = argv[0]; *p != '\0'; ++p)
		if (*p >= 'A' && *p <= 'Z')
			*p = *p - 'A' + 'a';
#endif

	progname = argv[0];
	return;
}