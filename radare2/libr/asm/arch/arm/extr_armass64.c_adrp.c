#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int ut64 ;
typedef  int ut32 ;
struct TYPE_5__ {TYPE_1__* operands; } ;
struct TYPE_4__ {scalar_t__ type; int reg; int immediate; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 scalar_t__ ARM_CONSTANT ; 
 scalar_t__ ARM_GPR ; 
 int UT32_MAX ; 
 int /*<<< orphan*/  eprintf (char*) ; 

__attribute__((used)) static ut32 adrp(ArmOp *op, ut64 addr, ut32 k) { //, int reg, ut64 dst) {
	ut64 at = 0LL;
	ut32 data = k;
	if (op->operands[0].type == ARM_GPR) {
		data += ((op->operands[0].reg & 0xff) << 24);
	} else {
		eprintf ("Usage: adrp x0, addr\n");
		return UT32_MAX;
	}
	if (op->operands[1].type == ARM_CONSTANT) {
		// XXX what about negative values?
		at = op->operands[1].immediate - addr;
		at /= 4;
	} else {
		eprintf ("Usage: adrp, x0, addr\n");
		return UT32_MAX;
	}
	ut8 b0 = at;
	ut8 b1 = (at >> 3) & 0xff;

#if 0
	ut8 b2 = (at >> (8 + 7)) & 0xff;
	data += b0 << 29;
	data += b1 << 16;
	data += b2 << 24;
#endif
	data += b0 << 16;
	data += b1 << 8;
	return data;
}