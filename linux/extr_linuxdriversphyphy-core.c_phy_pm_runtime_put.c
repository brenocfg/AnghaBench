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
struct phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  pm_runtime_enabled (int /*<<< orphan*/ *) ; 
 int pm_runtime_put (int /*<<< orphan*/ *) ; 

int phy_pm_runtime_put(struct phy *phy)
{
	if (!phy)
		return 0;

	if (!pm_runtime_enabled(&phy->dev))
		return -ENOTSUPP;

	return pm_runtime_put(&phy->dev);
}