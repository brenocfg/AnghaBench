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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 unsigned int CX2072X_UM_INTERRUPT_CRTL_E ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int cx2072x_reg_raw_write (void*,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int cx2072x_register_size (unsigned int) ; 

__attribute__((used)) static int cx2072x_reg_write(void *context, unsigned int reg,
			     unsigned int value)
{
	__le32 raw_value;
	unsigned int size;

	size = cx2072x_register_size(reg);

	if (reg == CX2072X_UM_INTERRUPT_CRTL_E) {
		/* Update the MSB byte only */
		reg += 3;
		size = 1;
		value >>= 24;
	}

	raw_value = cpu_to_le32(value);
	return cx2072x_reg_raw_write(context, reg, &raw_value, size);
}