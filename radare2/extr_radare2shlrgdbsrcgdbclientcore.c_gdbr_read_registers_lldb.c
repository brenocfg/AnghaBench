#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  data_len; } ;
typedef  TYPE_1__ libgdbr_t ;
struct TYPE_8__ {int valid; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf; scalar_t__ init; } ;

/* Variables and functions */
 int handle_lldb_read_reg (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_packet (TYPE_1__*,int) ; 
 TYPE_3__ reg_cache ; 
 scalar_t__ send_msg (TYPE_1__*,char*) ; 

__attribute__((used)) static int gdbr_read_registers_lldb(libgdbr_t *g) {
	// Send the stop reply query packet and get register info
	// (this is what lldb does)
	int ret;
	if (send_msg (g, "?") < 0 || read_packet (g, false) < 0) {
		return -1;
	}
	if ((ret = handle_lldb_read_reg (g)) < 0) {
		return ret;
	}
	if (reg_cache.init) {
		reg_cache.buflen = g->data_len;
		memcpy (reg_cache.buf, g->data, reg_cache.buflen);
		reg_cache.valid = true;
	}
	return 0;
}