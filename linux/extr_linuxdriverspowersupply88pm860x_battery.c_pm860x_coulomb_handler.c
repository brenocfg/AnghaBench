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
struct pm860x_battery_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  calc_ccnt (struct pm860x_battery_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccnt_data ; 

__attribute__((used)) static irqreturn_t pm860x_coulomb_handler(int irq, void *data)
{
	struct pm860x_battery_info *info = data;

	calc_ccnt(info, &ccnt_data);
	return IRQ_HANDLED;
}