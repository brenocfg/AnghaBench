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
struct phy {int /*<<< orphan*/  id; int /*<<< orphan*/  pwr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct phy*) ; 
 int /*<<< orphan*/  phy_ida ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 
 struct phy* to_phy (struct device*) ; 

__attribute__((used)) static void phy_release(struct device *dev)
{
	struct phy *phy;

	phy = to_phy(dev);
	dev_vdbg(dev, "releasing '%s'\n", dev_name(dev));
	regulator_put(phy->pwr);
	ida_simple_remove(&phy_ida, phy->id);
	kfree(phy);
}