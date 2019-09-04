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
struct bq27xxx_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ27XXX_REG_FCC ; 
 int bq27xxx_battery_read_charge (struct bq27xxx_device_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bq27xxx_battery_read_fcc(struct bq27xxx_device_info *di)
{
	return bq27xxx_battery_read_charge(di, BQ27XXX_REG_FCC);
}