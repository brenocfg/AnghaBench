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
struct device {int dummy; } ;
struct ag71xx_platform_data {int speed; int /*<<< orphan*/  duplex; } ;
struct ag71xx {int speed; int /*<<< orphan*/  duplex; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 struct ag71xx_platform_data* ag71xx_get_pdata (struct ag71xx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int ag71xx_phy_connect_fixed(struct ag71xx *ag)
{
	struct device *dev = &ag->pdev->dev;
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	int ret = 0;

	/* use fixed settings */
	switch (pdata->speed) {
	case SPEED_10:
	case SPEED_100:
	case SPEED_1000:
		break;
	default:
		dev_err(dev, "invalid speed specified\n");
		ret = -EINVAL;
		break;
	}

	dev_dbg(dev, "using fixed link parameters\n");

	ag->duplex = pdata->duplex;
	ag->speed = pdata->speed;

	return ret;
}