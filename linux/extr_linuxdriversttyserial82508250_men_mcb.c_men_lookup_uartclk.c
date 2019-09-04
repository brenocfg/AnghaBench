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
typedef  int u32 ;
struct mcb_device {int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static u32 men_lookup_uartclk(struct mcb_device *mdev)
{
	/* use default value if board is not available below */
	u32 clkval = 1041666;

	dev_info(&mdev->dev, "%s on board %s\n",
		dev_name(&mdev->dev),
		mdev->bus->name);
	if  (strncmp(mdev->bus->name, "F075", 4) == 0)
		clkval = 1041666;
	else if (strncmp(mdev->bus->name, "F216", 4) == 0)
		clkval = 1843200;
	else if (strncmp(mdev->bus->name, "G215", 4) == 0)
		clkval = 1843200;
	else if (strncmp(mdev->bus->name, "F210", 4) == 0)
		clkval = 115200;
	else
		dev_info(&mdev->dev,
			 "board not detected, using default uartclk\n");

	clkval = clkval  << 4;

	return clkval;
}