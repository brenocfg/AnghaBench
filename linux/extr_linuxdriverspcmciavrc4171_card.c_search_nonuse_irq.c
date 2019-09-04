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
 int vrc4171_irq_mask ; 

__attribute__((used)) static inline int search_nonuse_irq(void)
{
	int i;

	for (i = 0; i < 16; i++) {
		if (vrc4171_irq_mask & (1 << i)) {
			vrc4171_irq_mask &= ~(1 << i);
			return i;
		}
	}

	return -1;
}