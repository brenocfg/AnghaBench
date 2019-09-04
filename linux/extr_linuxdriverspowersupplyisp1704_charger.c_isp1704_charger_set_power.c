#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct isp1704_charger_data {int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  (* set_power ) (int) ;} ;
struct isp1704_charger {TYPE_1__* dev; } ;
struct TYPE_2__ {struct isp1704_charger_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void isp1704_charger_set_power(struct isp1704_charger *isp, bool on)
{
	struct isp1704_charger_data	*board = isp->dev->platform_data;

	if (board && board->set_power)
		board->set_power(on);
	else if (board)
		gpio_set_value(board->enable_gpio, on);
}