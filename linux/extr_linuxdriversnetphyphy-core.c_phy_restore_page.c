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
struct TYPE_4__ {TYPE_1__* bus; } ;
struct phy_device {TYPE_2__ mdio; } ;
struct TYPE_3__ {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int __phy_write_page (struct phy_device*,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int phy_restore_page(struct phy_device *phydev, int oldpage, int ret)
{
	int r;

	if (oldpage >= 0) {
		r = __phy_write_page(phydev, oldpage);

		/* Propagate the operation return code if the page write
		 * was successful.
		 */
		if (ret >= 0 && r < 0)
			ret = r;
	} else {
		/* Propagate the phy page selection error code */
		ret = oldpage;
	}

	mutex_unlock(&phydev->mdio.bus->mdio_lock);

	return ret;
}