#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_12__ {scalar_t__ core; scalar_t__ (* cfggeti ) (scalar_t__,char*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  reg; TYPE_2__ corebind; TYPE_1__* anal; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int bits; int /*<<< orphan*/  reg; } ;
typedef  TYPE_3__ RRegItem ;
typedef  TYPE_4__ RDebug ;

/* Variables and functions */
 int R_DEBUG_REASON_UNKNOWN ; 
 int /*<<< orphan*/  R_REG_NAME_PC ; 
 int buf_size ; 
 int /*<<< orphan*/  check_connection (TYPE_4__*) ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbr_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* r_reg_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_reg_get_bytes (int /*<<< orphan*/ ,int,int*) ; 
 char* r_reg_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_reg_get_value (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* r_reg_next_diff (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  r_swap_ut16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_swap_ut32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_swap_ut64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * reg_buf ; 
 scalar_t__ stub1 (scalar_t__,char*) ; 

__attribute__((used)) static int r_debug_gdb_reg_write(RDebug *dbg, int type, const ut8 *buf, int size) {
	check_connection (dbg);
	if (!desc) {
		return R_DEBUG_REASON_UNKNOWN;
	}
	if (!reg_buf) {
		// we cannot write registers before we once read them
		return -1;
	}
	int buflen = 0;
	int bits = dbg->anal->bits;
	const char *pcname = r_reg_get_name (dbg->anal->reg, R_REG_NAME_PC);
	RRegItem *reg = r_reg_get (dbg->anal->reg, pcname, 0);
	if (reg) {
		if (dbg->anal->bits != reg->size) {
			bits = reg->size;
		}
	}
	free (r_reg_get_bytes (dbg->reg, type, &buflen));
	// some implementations of the gdb protocol are acting weird.
	// so winedbg is not able to write registers through the <G> packet
	// and also it does not return the whole gdb register profile after\n"
	// calling <g>
	// so this workaround resizes the small register profile buffer
	// to the whole set and fills the rest with 0
	if (buf_size < buflen) {
		ut8* new_buf = realloc (reg_buf, buflen * sizeof (ut8));
		if (!new_buf) {
			return -1;
		}
		reg_buf = new_buf;
		memset (new_buf + buf_size, 0, buflen - buf_size);
	}

	RRegItem* current = NULL;
	// We default to little endian if there's no way to get the configuration,
	// since this was the behaviour prior to the change.
	bool bigendian = dbg->corebind.core && \
					 dbg->corebind.cfggeti (dbg->corebind.core, "cfg.bigendian");
	for (;;) {
		current = r_reg_next_diff (dbg->reg, type, reg_buf, buflen, current, bits);
		if (!current) {
			break;
		}
		ut64 val = r_reg_get_value (dbg->reg, current);
		int bytes = bits / 8;
		if (bigendian) {
			// TODO: validate that it's correct for all kinds of archs
			switch (bytes) {
			case 2:
				val = r_swap_ut16 (val);
				break;
			case 4:
				val = r_swap_ut32 (val);
				break;
			case 8:
			default:
				val = r_swap_ut64 (val);
				break;
			}
		}
		gdbr_write_reg (desc, current->name, (char*)&val, bytes);
	}
	return true;
}