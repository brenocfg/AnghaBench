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
#define  R_DACCRRDH 140 
#define  R_DACCRRDL 139 
#define  R_DACCRRDM 138 
#define  R_DACCRS 137 
#define  R_PLLSTAT 136 
#define  R_SPKCRRDH 135 
#define  R_SPKCRRDL 134 
#define  R_SPKCRRDM 133 
#define  R_SPKCRS 132 
#define  R_SUBCRRDH 131 
#define  R_SUBCRRDL 130 
#define  R_SUBCRRDM 129 
#define  R_SUBCRS 128 

__attribute__((used)) static bool tscs454_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case R_PLLSTAT:

	case R_SPKCRRDL:
	case R_SPKCRRDM:
	case R_SPKCRRDH:
	case R_SPKCRS:

	case R_DACCRRDL:
	case R_DACCRRDM:
	case R_DACCRRDH:
	case R_DACCRS:

	case R_SUBCRRDL:
	case R_SUBCRRDM:
	case R_SUBCRRDH:
	case R_SUBCRS:
		return true;
	default:
		return false;
	};
}