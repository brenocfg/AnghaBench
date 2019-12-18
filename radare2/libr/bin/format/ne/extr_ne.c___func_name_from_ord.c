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
typedef  int /*<<< orphan*/  ut16 ;
typedef  char Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  R2_SDB_FORMAT ; 
 int /*<<< orphan*/  R_JOIN_4_PATHS (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_file_exists (char*) ; 
 char* r_str_newf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  r_sys_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_close (char*) ; 
 char* sdb_get (char*,char*,int /*<<< orphan*/ *) ; 
 char* sdb_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *__func_name_from_ord(char *module, ut16 ordinal) {
	char *path = r_str_newf (R_JOIN_4_PATHS ("%s", R2_SDB_FORMAT, "dll", "%s.sdb"), r_sys_prefix (NULL), module);
	char *ord = r_str_newf ("%d", ordinal);
	char *name;
	if (r_file_exists (path)) {
		Sdb *sdb = sdb_new (NULL, path, 0);
		name = sdb_get (sdb, ord, NULL);
		if (!name) {
			name = ord;
		} else {
			free (ord);
		}
		sdb_close (sdb);
		free (sdb);
	} else {
		name = ord;
	}
	return name;
}