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
struct tps6524x {int dummy; } ;

/* Variables and functions */
 int __read_reg (struct tps6524x*,int) ; 
 int __write_reg (struct tps6524x*,int,int) ; 

__attribute__((used)) static int __rmw_reg(struct tps6524x *hw, int reg, int mask, int val)
{
	int ret;

	ret = __read_reg(hw, reg);
	if (ret < 0)
		return ret;

	ret &= ~mask;
	ret |= val;

	ret = __write_reg(hw, reg, ret);

	return (ret < 0) ? ret : 0;
}