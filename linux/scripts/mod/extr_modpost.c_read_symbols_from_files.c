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
 int PATH_MAX ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  read_symbols (char*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strends (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void read_symbols_from_files(const char *filename)
{
	FILE *in = stdin;
	char fname[PATH_MAX];

	if (strcmp(filename, "-") != 0) {
		in = fopen(filename, "r");
		if (!in)
			fatal("Can't open filenames file %s: %m", filename);
	}

	while (fgets(fname, PATH_MAX, in) != NULL) {
		if (strends(fname, "\n"))
			fname[strlen(fname)-1] = '\0';
		read_symbols(fname);
	}

	if (in != stdin)
		fclose(in);
}