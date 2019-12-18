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
 int asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static char *file_name_to_table_name(char *fname)
{
	unsigned int i;
	int n;
	int c;
	char *tblname;

	/*
	 * Ensure tablename starts with alphabetic character.
	 * Derive rest of table name from basename of the JSON file,
	 * replacing hyphens and stripping out .json suffix.
	 */
	n = asprintf(&tblname, "pme_%s", fname);
	if (n < 0) {
		pr_info("%s: asprintf() error %s for file %s\n", prog,
				strerror(errno), fname);
		return NULL;
	}

	for (i = 0; i < strlen(tblname); i++) {
		c = tblname[i];

		if (c == '-' || c == '/')
			tblname[i] = '_';
		else if (c == '.') {
			tblname[i] = '\0';
			break;
		} else if (!isalnum(c) && c != '_') {
			pr_err("%s: Invalid character '%c' in file name %s\n",
					prog, c, basename(fname));
			free(tblname);
			tblname = NULL;
			break;
		}
	}

	return tblname;
}