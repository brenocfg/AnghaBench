#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_11__ {int /*<<< orphan*/  reg; TYPE_1__* anal; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int bits; int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RRegItem ;
typedef  TYPE_3__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_NAME_PC ; 
 int buf_size ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qnxr_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* r_reg_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_reg_get_bytes (int /*<<< orphan*/ ,int,int*) ; 
 char* r_reg_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_reg_get_value (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* r_reg_next_diff (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * reg_buf ; 

__attribute__((used)) static int r_debug_qnx_reg_write (RDebug *dbg, int type, const ut8 *buf, int size) {
	int buflen = 0;
	int bits = dbg->anal->bits;
	const char *pcname = r_reg_get_name (dbg->anal->reg, R_REG_NAME_PC);
	RRegItem *reg = r_reg_get (dbg->anal->reg, pcname, 0);
	if (!reg_buf) {
		// we cannot write registers before we once read them
		return -1;
	}
	if (reg) {
		if (dbg->anal->bits != reg->size) {
			bits = reg->size;
		}
	}
	free (r_reg_get_bytes (dbg->reg, type, &buflen));
	// some implementations of the gdb protocol are acting weird.
	// so winedbg is not able to write registers through the <G> packet
	// and also it does not return the whole gdb register profile after
	// calling <g>
	// so this workaround resizes the small register profile buffer
	// to the whole set and fills the rest with 0
	if (buf_size < buflen) {
		ut8 *new_buf = realloc (reg_buf, buflen * sizeof (ut8));
		if (!new_buf) {
			return -1;
		}
		reg_buf = new_buf;
		memset (new_buf + buf_size, 0, buflen - buf_size);
	}

	RRegItem *current = NULL;
	for (;;) {
		current = r_reg_next_diff (dbg->reg, type, reg_buf, buflen, current, bits);
		if (!current) {
			break;
		}
		ut64 val = r_reg_get_value (dbg->reg, current);
		int bytes = bits / 8;
		qnxr_write_reg (desc, current->name, (char *)&val, bytes);
	}
	return true;
}