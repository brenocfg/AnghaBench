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
struct phy_ops {int dummy; } ;
struct phy {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct phy*) ; 
 int /*<<< orphan*/  devm_phy_consume ; 
 int /*<<< orphan*/  devres_add (struct device*,struct phy**) ; 
 struct phy** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct phy**) ; 
 struct phy* phy_create (struct device*,struct device_node*,struct phy_ops const*) ; 

struct phy *devm_phy_create(struct device *dev, struct device_node *node,
			    const struct phy_ops *ops)
{
	struct phy **ptr, *phy;

	ptr = devres_alloc(devm_phy_consume, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	phy = phy_create(dev, node, ops);
	if (!IS_ERR(phy)) {
		*ptr = phy;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return phy;
}