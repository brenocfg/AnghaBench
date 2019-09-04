#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
struct TYPE_3__ {int addr; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */

__attribute__((used)) static ut64 disarm_12bit_offset (RAnalOp *op, unsigned int insoff) {
	ut64 off = insoff;
	/* sign extend if higher bit is 1 (0x0800) */
	if ((off & 0x0800) == 0x0800)
	{
		off |= ~0xFFF;
	}
	return (op->addr) + (off << 1) + 4;
}