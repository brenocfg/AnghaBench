#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  g; } ;
struct TYPE_11__ {TYPE_1__ lldb; } ;
struct TYPE_12__ {scalar_t__ remote_type; int /*<<< orphan*/  data; int /*<<< orphan*/  data_len; TYPE_2__ stub_features; } ;
typedef  TYPE_3__ libgdbr_t ;
struct TYPE_13__ {int valid; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf; scalar_t__ init; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READREGS ; 
 scalar_t__ GDB_REMOTE_TYPE_LLDB ; 
 int gdbr_read_registers_lldb (TYPE_3__*) ; 
 scalar_t__ handle_g (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
	if (g->remote_type == GDB_REMOTE_TYPE_LLDB
	    && !g->stub_features.lldb.g) {
		return gdbr_read_registers_lldb (g);
	}
	ret = send_msg (g, CMD_READREGS);
	if (ret < 0) {
		return ret;
	}
	if (read_packet (g, false) < 0 || handle_g (g) < 0) {
		return -1;
	}
	if (reg_cache.init) {
		reg_cache.buflen = g->data_len;
		memset (reg_cache.buf, 0, reg_cache.buflen);
		memcpy (reg_cache.buf, g->data, reg_cache.buflen);
		reg_cache.valid = true;
	}
	return 0;
}