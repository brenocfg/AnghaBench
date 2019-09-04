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

/* Variables and functions */

__attribute__((used)) static unsigned int disarm_branch_offset(unsigned int pc, unsigned int insoff) {
	unsigned int add = insoff << 2;
	/* zero extend if higher is 1 (0x02000000) */
	if ((add & 0x02000000) == 0x02000000) {
		add |= 0xFC000000;
	}
	return add + pc + 8;
}