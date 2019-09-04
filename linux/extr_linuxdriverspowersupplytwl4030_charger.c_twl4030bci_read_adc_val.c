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
typedef  int u8 ;

/* Variables and functions */
 int twl4030_bci_read (int,int*) ; 

__attribute__((used)) static int twl4030bci_read_adc_val(u8 reg)
{
	int ret, temp;
	u8 val;

	/* read MSB */
	ret = twl4030_bci_read(reg + 1, &val);
	if (ret)
		return ret;

	temp = (int)(val & 0x03) << 8;

	/* read LSB */
	ret = twl4030_bci_read(reg, &val);
	if (ret)
		return ret;

	return temp | val;
}