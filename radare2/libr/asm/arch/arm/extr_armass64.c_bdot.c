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
typedef  scalar_t__ ut64 ;
typedef  int ut32 ;
struct TYPE_5__ {TYPE_1__* operands; } ;
struct TYPE_4__ {int immediate; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 int UT32_MAX ; 
 int calcNegOffset (int,int) ; 

__attribute__((used)) static ut32 bdot(ArmOp *op, ut64 addr, int k) {
	ut32 data = UT32_MAX;
	int n = 0;
	int a = 0;
	n = op->operands[0].immediate;
	// I am sure there's a logical way to do negative offsets,
	// but I was unable to find any sensible docs so I did my best
	if (!(n & 0x3 || n > 0x7ffffff)) {
		n -= addr;
		data = k;
		if (n < 0) {
			n *= -1;
			a = (n << 3) - 1;
			data |= (0xff - a) << 24;

			a = calcNegOffset(n, 5);
			data |= a << 16;

			a = calcNegOffset(n, 13);
			data |= a << 8;
		} else {
			data |= (n & 31) << 27;
			data |= (0xff & (n >> 5)) << 16;
			data |= (0xff & (n >> 13)) << 8;
		}
	}

	return data;
}