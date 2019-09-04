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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {struct dp83640_private* priv; } ;
struct dp83640_private {TYPE_1__* clock; } ;
struct TYPE_2__ {int page; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGESEL ; 
 int /*<<< orphan*/  broadcast_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext_read(struct phy_device *phydev, int page, u32 regnum)
{
	struct dp83640_private *dp83640 = phydev->priv;
	int val;

	if (dp83640->clock->page != page) {
		broadcast_write(phydev, PAGESEL, page);
		dp83640->clock->page = page;
	}
	val = phy_read(phydev, regnum);

	return val;
}