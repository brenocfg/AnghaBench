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
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 
 char* sdb_querys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void cmd_sdbk(Sdb *db, const char *input) {
	char *out = (input[0] == ' ')
		? sdb_querys (db, NULL, 0, input + 1)
		: sdb_querys (db, NULL, 0, "*");
	if (out) {
		r_cons_println (out);
		free (out);
	} else {
		eprintf ("|ERROR| Usage: ask [query]\n");
	}
}