#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kgdb_state {int /*<<< orphan*/  linux_regs; int /*<<< orphan*/  err_code; int /*<<< orphan*/  signo; int /*<<< orphan*/  ex_vector; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_char ) (char) ;} ;

/* Variables and functions */
 TYPE_1__* dbg_io_ops ; 
 int /*<<< orphan*/  gdbstub_prev_in_buf_pos ; 
 int /*<<< orphan*/  gdbstub_use_prev_in_buf ; 
 int kgdb_arch_handle_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remcom_in_buffer ; 
 int /*<<< orphan*/  remcom_out_buffer ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char) ; 

int gdbstub_state(struct kgdb_state *ks, char *cmd)
{
	int error;

	switch (cmd[0]) {
	case 'e':
		error = kgdb_arch_handle_exception(ks->ex_vector,
						   ks->signo,
						   ks->err_code,
						   remcom_in_buffer,
						   remcom_out_buffer,
						   ks->linux_regs);
		return error;
	case 's':
	case 'c':
		strcpy(remcom_in_buffer, cmd);
		return 0;
	case '$':
		strcpy(remcom_in_buffer, cmd);
		gdbstub_use_prev_in_buf = strlen(remcom_in_buffer);
		gdbstub_prev_in_buf_pos = 0;
		return 0;
	}
	dbg_io_ops->write_char('+');
	put_packet(remcom_out_buffer);
	return 0;
}