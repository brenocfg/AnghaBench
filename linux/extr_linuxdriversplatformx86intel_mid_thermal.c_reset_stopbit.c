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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int intel_msic_reg_read (int /*<<< orphan*/ ,int*) ; 
 int intel_msic_reg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int reset_stopbit(uint16_t addr)
{
	int ret;
	uint8_t data;
	ret = intel_msic_reg_read(addr, &data);
	if (ret)
		return ret;
	/* Set the stop bit to zero */
	return intel_msic_reg_write(addr, (data & 0xEF));
}