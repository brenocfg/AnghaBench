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
struct phy {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 struct phy* _of_phy_get (struct device_node*,int) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int of_property_match_string (struct device_node*,char*,char const*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct phy *of_phy_get(struct device_node *np, const char *con_id)
{
	struct phy *phy = NULL;
	int index = 0;

	if (con_id)
		index = of_property_match_string(np, "phy-names", con_id);

	phy = _of_phy_get(np, index);
	if (IS_ERR(phy))
		return phy;

	if (!try_module_get(phy->ops->owner))
		return ERR_PTR(-EPROBE_DEFER);

	get_device(&phy->dev);

	return phy;
}