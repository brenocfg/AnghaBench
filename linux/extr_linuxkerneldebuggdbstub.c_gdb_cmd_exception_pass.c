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
struct kgdb_state {int pass_exception; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_remove_all_break () ; 
 int /*<<< orphan*/  gdbstub_msg_write (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kgdb_connected ; 
 char* remcom_in_buffer ; 

__attribute__((used)) static int gdb_cmd_exception_pass(struct kgdb_state *ks)
{
	/* C09 == pass exception
	 * C15 == detach kgdb, pass exception
	 */
	if (remcom_in_buffer[1] == '0' && remcom_in_buffer[2] == '9') {

		ks->pass_exception = 1;
		remcom_in_buffer[0] = 'c';

	} else if (remcom_in_buffer[1] == '1' && remcom_in_buffer[2] == '5') {

		ks->pass_exception = 1;
		remcom_in_buffer[0] = 'D';
		dbg_remove_all_break();
		kgdb_connected = 0;
		return 1;

	} else {
		gdbstub_msg_write("KGDB only knows signal 9 (pass)"
			" and 15 (pass and disconnect)\n"
			"Executing a continue without signal passing\n", 0);
		remcom_in_buffer[0] = 'c';
	}

	/* Indicate fall through */
	return -1;
}