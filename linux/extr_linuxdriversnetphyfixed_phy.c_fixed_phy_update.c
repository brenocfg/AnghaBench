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
struct TYPE_2__ {int link; } ;
struct fixed_phy {int /*<<< orphan*/  link_gpio; TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_get_value_cansleep (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fixed_phy_update(struct fixed_phy *fp)
{
	if (gpio_is_valid(fp->link_gpio))
		fp->status.link = !!gpio_get_value_cansleep(fp->link_gpio);
}