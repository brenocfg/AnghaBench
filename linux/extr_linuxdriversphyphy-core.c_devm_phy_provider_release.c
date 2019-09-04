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
struct phy_provider {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_phy_provider_unregister (struct phy_provider*) ; 

__attribute__((used)) static void devm_phy_provider_release(struct device *dev, void *res)
{
	struct phy_provider *phy_provider = *(struct phy_provider **)res;

	of_phy_provider_unregister(phy_provider);
}