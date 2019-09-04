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
 int /*<<< orphan*/  DOING_KGDB ; 
 int /*<<< orphan*/  KDB_STATE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KGDB_TRANS ; 
 int /*<<< orphan*/  kdb_gdb_state_pass (char*) ; 
 int /*<<< orphan*/  kdb_printf (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int kgdb_transition_check(char *buffer)
{
	if (buffer[0] != '+' && buffer[0] != '$') {
		KDB_STATE_SET(KGDB_TRANS);
		kdb_printf("%s", buffer);
	} else {
		int slen = strlen(buffer);
		if (slen > 3 && buffer[slen - 3] == '#') {
			kdb_gdb_state_pass(buffer);
			strcpy(buffer, "kgdb");
			KDB_STATE_SET(DOING_KGDB);
			return 1;
		}
	}
	return 0;
}