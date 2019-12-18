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

__attribute__((used)) static int mips_r(ut8 *b, int op, int rs, int rt, int rd, int sa, int fun) {
//^this will keep the below mips_r fuctions working
// diff instructions use a diff arg order (add is rd, rs, rt - sll is rd, rt, sa - sllv is rd, rt, rs
//static int mips_r (ut8 *b, int op, int rd, int rs, int rt, int sa, int fun) {
	if (rs == -1 || rt == -1) {
		return -1;
	}
	b[3] = ((op<<2)&0xfc) | ((rs>>3)&3); // 2
	b[2] = (rs<<5) | (rt&0x1f); // 1
	b[1] = ((rd<<3)&0xff) | (sa>>2); // 0
	b[0] = (fun&0x3f) | ((sa&3)<<6);
	return 4;
}