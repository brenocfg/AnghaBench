#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  g; } ;
struct TYPE_13__ {TYPE_1__ lldb; } ;
struct TYPE_14__ {scalar_t__ remote_type; int /*<<< orphan*/  data; int /*<<< orphan*/  data_len; TYPE_2__ stub_features; int /*<<< orphan*/  gdbr_lock; } ;
typedef  TYPE_3__ libgdbr_t ;
struct TYPE_15__ {int valid; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf; scalar_t__ init; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READREGS ; 
 scalar_t__ GDB_REMOTE_TYPE_LLDB ; 
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_3__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_3__*) ; 
 int gdbr_read_registers_lldb (TYPE_3__*) ; 
 scalar_t__ handle_g (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_th_lock_check (int /*<<< orphan*/ ) ; 
 scalar_t__ read_packet (TYPE_3__*,int) ; 
 TYPE_5__ reg_cache ; 
 int send_msg (TYPE_3__*,int /*<<< orphan*/ ) ; 

int gdbr_read_registers(libgdbr_t *g) {
	int ret = -1;

	if (!g || !g->data) {
		return -1;
	}
	if (reg_cache.init && reg_cache.valid) {
		g->data_len = reg_cache.buflen;
		memcpy (g->data, reg_cache.buf, reg_cache.buflen);
		return 0;
	}
	// Don't wait on the lock in read_registers since it's frequently called, including
	// each time "enter" is pressed. Otherwise the user will be forced to interrupt exit
	// read_registers constantly while another task is in progress
	if (r_th_lock_check (g->gdbr_lock)) {
		return -1;
	}

	if (!gdbr_lock_enter (g)) {
		goto end;
	}
	if (g->remote_type == GDB_REMOTE_TYPE_LLDB && !g->stub_features.lldb.g) {
		ret = gdbr_read_registers_lldb (g);
		goto end;
	}
	if ((ret = send_msg (g, CMD_READREGS)) < 0) {
		goto end;
	}
	if (read_packet (g, false) < 0 || handle_g (g) < 0) {
		ret = -1;
		goto end;
	}
	if (reg_cache.init) {
		reg_cache.buflen = g->data_len;
		memset (reg_cache.buf, 0, reg_cache.buflen);
		memcpy (reg_cache.buf, g->data, reg_cache.buflen);
		reg_cache.valid = true;
	}

	ret = 0;
end:
	gdbr_lock_leave (g);
	return ret;
}