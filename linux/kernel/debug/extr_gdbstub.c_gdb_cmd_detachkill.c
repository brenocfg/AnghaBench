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
struct kgdb_state {int dummy; } ;

/* Variables and functions */
 int dbg_remove_all_break () ; 
 int /*<<< orphan*/  error_packet (int /*<<< orphan*/ ,int) ; 
 scalar_t__ kgdb_connected ; 
 int /*<<< orphan*/  put_packet (int /*<<< orphan*/ ) ; 
 char* remcom_in_buffer ; 
 int /*<<< orphan*/  remcom_out_buffer ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void gdb_cmd_detachkill(struct kgdb_state *ks)
{
	int error;

	/* The detach case */
	if (remcom_in_buffer[0] == 'D') {
		error = dbg_remove_all_break();
		if (error < 0) {
			error_packet(remcom_out_buffer, error);
		} else {
			strcpy(remcom_out_buffer, "OK");
			kgdb_connected = 0;
		}
		put_packet(remcom_out_buffer);
	} else {
		/*
		 * Assume the kill case, with no exit code checking,
		 * trying to force detach the debugger:
		 */
		dbg_remove_all_break();
		kgdb_connected = 0;
	}
}