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
struct device {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int OFFSET_COARSE ; 
 int /*<<< orphan*/  OFFSET_SIGN_BIT ; 
 long OFFSET_STEP ; 
 int /*<<< orphan*/  PCF2123_REG_OFFSET ; 
 int pcf2123_read (struct device*,int /*<<< orphan*/ ,int*,int) ; 
 int sign_extend32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf2123_read_offset(struct device *dev, long *offset)
{
	int ret;
	s8 reg;

	ret = pcf2123_read(dev, PCF2123_REG_OFFSET, &reg, 1);
	if (ret < 0)
		return ret;

	if (reg & OFFSET_COARSE)
		reg <<= 1; /* multiply by 2 and sign extend */
	else
		reg = sign_extend32(reg, OFFSET_SIGN_BIT);

	*offset = ((long)reg) * OFFSET_STEP;

	return 0;
}