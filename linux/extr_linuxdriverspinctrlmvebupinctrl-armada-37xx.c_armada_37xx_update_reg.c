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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned int GPIO_PER_REG ; 

__attribute__((used)) static inline void armada_37xx_update_reg(unsigned int *reg,
					  unsigned int offset)
{
	/* We never have more than 2 registers */
	if (offset >= GPIO_PER_REG) {
		offset -= GPIO_PER_REG;
		*reg += sizeof(u32);
	}
}