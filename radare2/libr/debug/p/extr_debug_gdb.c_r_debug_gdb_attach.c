#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* io; } ;
struct TYPE_16__ {int swstep; int /*<<< orphan*/  arch; TYPE_4__* anal; TYPE_2__ iob; } ;
struct TYPE_15__ {TYPE_5__* data; TYPE_3__* plugin; } ;
struct TYPE_14__ {int /*<<< orphan*/  desc; } ;
struct TYPE_13__ {int bits; } ;
struct TYPE_12__ {scalar_t__ name; } ;
struct TYPE_10__ {TYPE_6__* desc; } ;
typedef  TYPE_5__ RIOGdb ;
typedef  TYPE_6__ RIODesc ;
typedef  TYPE_7__ RDebug ;

/* Variables and functions */
#define  R_SYS_ARCH_ARM 134 
#define  R_SYS_ARCH_AVR 133 
#define  R_SYS_ARCH_LM32 132 
#define  R_SYS_ARCH_MIPS 131 
#define  R_SYS_ARCH_SH 130 
#define  R_SYS_ARCH_V850 129 
#define  R_SYS_ARCH_X86 128 
 void* UNKNOWN ; 
 int /*<<< orphan*/ * desc ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  gdbr_set_architecture (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_5__** origriogdb ; 
 int r_sys_arch_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 void* support_hw_bp ; 
 void* support_sw_bp ; 

__attribute__((used)) static int r_debug_gdb_attach(RDebug *dbg, int pid) {
	RIODesc *d = dbg->iob.io->desc;
	// TODO: the core must update the dbg.swstep config var when this var is changed
	dbg->swstep = false;
	//eprintf ("XWJSTEP TOFALSE\n");
	if (d && d->plugin && d->plugin->name && d->data) {
		if (!strcmp ("gdb", d->plugin->name)) {
			RIOGdb *g = d->data;
			origriogdb = (RIOGdb **)&d->data;	//TODO bit of a hack, please improve
			support_sw_bp = UNKNOWN;
			support_hw_bp = UNKNOWN;
			int arch = r_sys_arch_id (dbg->arch);
			int bits = dbg->anal->bits;
			desc = &g->desc;
			switch (arch) {
			case R_SYS_ARCH_X86:
				if (bits == 16 || bits == 32) {
					gdbr_set_architecture (desc, "x86", 32);
				} else if (bits == 64) {
					gdbr_set_architecture (desc, "x86", 64);
				} else {
					eprintf ("Not supported register %s %d profile\n", dbg->arch, bits);
					return false;
				}
				break;
			case R_SYS_ARCH_SH:
				// TODO
				break;
			case R_SYS_ARCH_ARM:
				if (bits == 16 || bits == 32) {
					gdbr_set_architecture (desc, "arm", 32);
				} else if (bits == 64) {
					gdbr_set_architecture (desc, "arm", 64);
				} else {
					eprintf ("Not supported register %s %d profile\n", dbg->arch, bits);
					return false;
				}
				break;
			case R_SYS_ARCH_LM32:
				if (bits == 32) {
					gdbr_set_architecture(desc, "lm32", 32);
				} else {
					eprintf ("Not supported register %s %d profile\n", dbg->arch, bits);
					return false;
				}
				break;
			case R_SYS_ARCH_MIPS:
				if (bits == 32 || bits == 64) {
					gdbr_set_architecture (desc, "mips", bits);
				} else {
					eprintf ("Not supported register %s %d profile\n", dbg->arch, bits);
					return false;
				}
				break;
			case R_SYS_ARCH_AVR:
				gdbr_set_architecture (desc, "avr", 16);
				break;
			case R_SYS_ARCH_V850:
				gdbr_set_architecture (desc, "v850", 32);
				break;
			}
		} else {
			eprintf ("ERROR: Underlying IO descriptor is not a GDB one..\n");
		}
	}
	return true;
}