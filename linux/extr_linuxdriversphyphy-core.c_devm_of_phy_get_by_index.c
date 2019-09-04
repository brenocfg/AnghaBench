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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 struct phy* _of_phy_get (struct device_node*,int) ; 
 int /*<<< orphan*/  devm_phy_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct phy**) ; 
 struct phy** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct phy**) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct phy *devm_of_phy_get_by_index(struct device *dev, struct device_node *np,
				     int index)
{
	struct phy **ptr, *phy;

	ptr = devres_alloc(devm_phy_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	phy = _of_phy_get(np, index);
	if (IS_ERR(phy)) {
		devres_free(ptr);
		return phy;
	}

	if (!try_module_get(phy->ops->owner)) {
		devres_free(ptr);
		return ERR_PTR(-EPROBE_DEFER);
	}

	get_device(&phy->dev);

	*ptr = phy;
	devres_add(dev, ptr);

	return phy;
}