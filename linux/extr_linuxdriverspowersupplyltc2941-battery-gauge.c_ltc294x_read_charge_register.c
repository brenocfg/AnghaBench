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
struct ltc294x_info {int /*<<< orphan*/  client; } ;
typedef  enum ltc294x_reg { ____Placeholder_ltc294x_reg } ltc294x_reg ;

/* Variables and functions */
 int ltc294x_read_regs (int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int ltc294x_read_charge_register(const struct ltc294x_info *info,
					enum ltc294x_reg reg)
 {
	int ret;
	u8 datar[2];

	ret = ltc294x_read_regs(info->client, reg, &datar[0], 2);
	if (ret < 0)
		return ret;
	return (datar[0] << 8) + datar[1];
}