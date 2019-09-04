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
struct uwb_pal {TYPE_2__* rc; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 

__attribute__((used)) static void uwb_dbg_channel_changed(struct uwb_pal *pal, int channel)
{
	struct device *dev = &pal->rc->uwb_dev.dev;

	if (channel > 0)
		dev_info(dev, "debug: channel %d started\n", channel);
	else
		dev_info(dev, "debug: channel stopped\n");
}