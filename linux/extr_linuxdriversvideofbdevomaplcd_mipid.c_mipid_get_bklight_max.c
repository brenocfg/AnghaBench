#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mipid_platform_data {unsigned int (* get_bklight_max ) (struct mipid_platform_data*) ;} ;
struct mipid_device {TYPE_2__* spi; } ;
struct lcd_panel {int dummy; } ;
struct TYPE_3__ {struct mipid_platform_data* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 unsigned int ENODEV ; 
 unsigned int stub1 (struct mipid_platform_data*) ; 
 struct mipid_device* to_mipid_device (struct lcd_panel*) ; 

__attribute__((used)) static unsigned int mipid_get_bklight_max(struct lcd_panel *panel)
{
	struct mipid_device *md = to_mipid_device(panel);
	struct mipid_platform_data *pd = md->spi->dev.platform_data;

	if (pd->get_bklight_max == NULL)
		return -ENODEV;

	return pd->get_bklight_max(pd);
}