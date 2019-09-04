#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ut8 ;

/* Variables and functions */

__attribute__((used)) static int mips_i(ut8 *b, int op, int rs, int rt, int imm, int is_branch) {
	if (rs == -1 || rt == -1) {
		return -1;
	}
	if (is_branch) {
		if (imm > 4) {
			imm /= 4;
			imm--;
		} else {
			imm = 0;
		}
	}
	b[3] = ((op<<2)&0xfc) | ((rs>>3)&3);
	b[2] = (rs<<5) | (rt);
	b[1] = (imm>>8) &0xff;
	b[0] = imm & 0xff;
	return 4;
}