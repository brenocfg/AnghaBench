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
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  insertkeys (int /*<<< orphan*/ ,char const**,int,char) ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  s ; 
 int /*<<< orphan*/  sdb_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_disk_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_disk_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_disk_insert (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sdb_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* stdin_slurp (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int createdb(const char *f, const char **args, int nargs) {
	char *line, *eq;
	s = sdb_new (NULL, f, 0);
	if (!s || !sdb_disk_create (s)) {
		eprintf ("Cannot create database\n");
		return 1;
	}
	insertkeys (s, args, nargs, '=');
	sdb_config (s, options);
	for (; (line = stdin_slurp (NULL));) {
		if ((eq = strchr (line, '='))) {
			*eq++ = 0;
			sdb_disk_insert (s, line, eq);
		}
		free (line);
	}
	sdb_disk_finish (s);
	return 0;
}