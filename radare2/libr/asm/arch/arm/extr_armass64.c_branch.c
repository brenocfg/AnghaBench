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
typedef  int ut64 ;
typedef  int ut32 ;
struct TYPE_5__ {TYPE_1__* operands; } ;
struct TYPE_4__ {int type; int immediate; int reg; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 int ARM_CONSTANT ; 
 int UT32_MAX ; 

__attribute__((used)) static ut32 branch(ArmOp *op, ut64 addr, int k) {
	ut32 data = UT32_MAX;
	int n = 0;
	if (op->operands[0].type & ARM_CONSTANT) {
		n = op->operands[0].immediate;
		if (!(n & 0x3 || n > 0x7ffffff)) {
			if (n >= addr) {
				n -= addr;
			} else {
				n -= addr;
				n = n & 0xfffffff;
				k |= 3;
			}
			n = n >> 2;
			int t = n >> 24;
			int h = n >> 16;
			int m = (n & 0xff00) >> 8;
			n &= 0xff;
			data = k;
			data |= n << 24;
			data |= m << 16;
			data |= h << 8;
			data |= t;
		}
	} else {
		n = op->operands[0].reg;
		if (n < 0 || n > 31) {
			return -1;
		}
		n = n << 5;
		int h = n >> 8;
		n &= 0xff;
		data = k;
		data |= n << 24;
		data |= h << 16;
	}
	return data;
}