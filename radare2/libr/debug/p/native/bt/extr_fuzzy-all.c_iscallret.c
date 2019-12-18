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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  long long ut64 ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_6__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* read_at ) (int /*<<< orphan*/ ,long long,int*,int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  anal; TYPE_1__ iob; scalar_t__ arch; } ;
typedef  TYPE_2__ RDebug ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_MASK_BASIC ; 
 scalar_t__ R_ANAL_OP_TYPE_CALL ; 
 scalar_t__ R_ANAL_OP_TYPE_UCALL ; 
 long long UT64_MAX ; 
 int /*<<< orphan*/  r_anal_op (int /*<<< orphan*/ ,TYPE_3__*,long long,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,long long,int*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,long long,int*,int) ; 

__attribute__((used)) static int iscallret(RDebug *dbg, ut64 addr) {
	ut8 buf[32];
	if (addr == 0LL || addr == UT64_MAX)
		return 0;
	/* check if region is executable */
	/* check if previous instruction is a call */
	/* if x86 expect CALL to be 5 byte length */
	if (dbg->arch && !strcmp (dbg->arch, "x86")) {
		(void)dbg->iob.read_at (dbg->iob.io, addr-5, buf, 5);
		if (buf[0] == 0xe8) {
			return 1;
		}
		if (buf[3] == 0xff  /* bits 4-5 (from right) of next byte must be 01 */
		    && ((buf[4] & 0xf0) == 0xd0  /* Mod is 11 */
		        || ((buf[4] & 0xf0) == 0x10  /* Mod is 00 */
		            && (buf[4] & 0x06) != 0x04))) {  /* R/M not 10x */
			return 1;
		}
		// IMMAMISSINGANYOP
	} else {
		RAnalOp op;
		(void) dbg->iob.read_at (dbg->iob.io, addr-8, buf, 8);
		(void) r_anal_op (dbg->anal, &op, addr-8, buf, 8, R_ANAL_OP_MASK_BASIC);
		if (op.type == R_ANAL_OP_TYPE_CALL || op.type == R_ANAL_OP_TYPE_UCALL) {
			return 1;
		}
		/* delay slot */
		(void) r_anal_op (dbg->anal, &op, addr-4, buf, 4, R_ANAL_OP_MASK_BASIC);
		if (op.type == R_ANAL_OP_TYPE_CALL || op.type == R_ANAL_OP_TYPE_UCALL) {
			return 1;
		}
	}
	return 0;
}