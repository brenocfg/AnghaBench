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
#define  LP8720_BUCK_VOUT1 133 
#define  LP8720_BUCK_VOUT2 132 
#define  LP8725_BUCK1_VOUT1 131 
#define  LP8725_BUCK1_VOUT2 130 
#define  LP8725_BUCK2_VOUT1 129 
#define  LP8725_BUCK2_VOUT2 128 

__attribute__((used)) static bool lp872x_is_valid_buck_addr(u8 addr)
{
	switch (addr) {
	case LP8720_BUCK_VOUT1:
	case LP8720_BUCK_VOUT2:
	case LP8725_BUCK1_VOUT1:
	case LP8725_BUCK1_VOUT2:
	case LP8725_BUCK2_VOUT1:
	case LP8725_BUCK2_VOUT2:
		return true;
	default:
		return false;
	}
}