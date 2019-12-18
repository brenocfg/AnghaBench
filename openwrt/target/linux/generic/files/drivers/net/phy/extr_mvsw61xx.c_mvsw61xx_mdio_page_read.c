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
struct switch_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_MV_PAGE ; 
 int mvsw61xx_mdio_read (struct switch_dev*,int,int) ; 
 int /*<<< orphan*/  mvsw61xx_mdio_write (struct switch_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mvsw61xx_mdio_page_read(struct switch_dev *dev, int port, int page, int reg)
{
	int ret;

	mvsw61xx_mdio_write(dev, port, MII_MV_PAGE, page);
	ret = mvsw61xx_mdio_read(dev, port, reg);
	mvsw61xx_mdio_write(dev, port, MII_MV_PAGE, 0);

	return ret;
}