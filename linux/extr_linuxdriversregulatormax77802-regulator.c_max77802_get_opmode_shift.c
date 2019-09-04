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
 int EINVAL ; 
 int MAX77802_BUCK1 ; 
 int MAX77802_BUCK10 ; 
 int MAX77802_BUCK2 ; 
 int MAX77802_BUCK4 ; 
 int MAX77802_BUCK5 ; 
 int MAX77802_LDO1 ; 
 int MAX77802_LDO35 ; 
 int MAX77802_OPMODE_BUCK234_SHIFT ; 
 int MAX77802_OPMODE_SHIFT_LDO ; 

__attribute__((used)) static int max77802_get_opmode_shift(int id)
{
	if (id == MAX77802_BUCK1 || (id >= MAX77802_BUCK5 &&
				     id <= MAX77802_BUCK10))
		return 0;

	if (id >= MAX77802_BUCK2 && id <= MAX77802_BUCK4)
		return MAX77802_OPMODE_BUCK234_SHIFT;

	if (id >= MAX77802_LDO1 && id <= MAX77802_LDO35)
		return MAX77802_OPMODE_SHIFT_LDO;

	return -EINVAL;
}