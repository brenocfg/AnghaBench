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

/* Variables and functions */
#define  R_DACCRADDR 136 
#define  R_DACCRRDH 135 
#define  R_DACCRRDL 134 
#define  R_DACCRRDM 133 
#define  R_DACCRSTAT 132 
#define  R_DACCRWRH 131 
#define  R_DACCRWRL 130 
#define  R_DACCRWRM 129 
#define  R_PLLCTL0 128 

__attribute__((used)) static bool tscs42xx_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case R_DACCRWRL:
	case R_DACCRWRM:
	case R_DACCRWRH:
	case R_DACCRRDL:
	case R_DACCRRDM:
	case R_DACCRRDH:
	case R_DACCRSTAT:
	case R_DACCRADDR:
	case R_PLLCTL0:
		return true;
	default:
		return false;
	};
}