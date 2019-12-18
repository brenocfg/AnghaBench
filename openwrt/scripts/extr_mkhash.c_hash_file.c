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
struct hash_type {char* (* func ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* stub1 (int /*<<< orphan*/ *) ; 
 char* stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hash_file(struct hash_type *t, const char *filename, bool add_filename)
{
	const char *str;

	if (!filename || !strcmp(filename, "-")) {
		str = t->func(stdin);
	} else {
		FILE *f = fopen(filename, "r");

		if (!f) {
			fprintf(stderr, "Failed to open '%s'\n", filename);
			return 1;
		}
		str = t->func(f);
		fclose(f);
	}

	if (!str) {
		fprintf(stderr, "Failed to generate hash\n");
		return 1;
	}

	if (add_filename)
		printf("%s %s\n", str, filename ? filename : "-");
	else
		printf("%s\n", str);
	return 0;
}