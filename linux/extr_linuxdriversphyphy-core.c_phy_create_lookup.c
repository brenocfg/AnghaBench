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
struct phy_lookup {char const* dev_id; char const* con_id; int /*<<< orphan*/  node; struct phy* phy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct phy_lookup* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_provider_mutex ; 
 int /*<<< orphan*/  phys ; 

int phy_create_lookup(struct phy *phy, const char *con_id, const char *dev_id)
{
	struct phy_lookup *pl;

	if (!phy || !dev_id || !con_id)
		return -EINVAL;

	pl = kzalloc(sizeof(*pl), GFP_KERNEL);
	if (!pl)
		return -ENOMEM;

	pl->dev_id = dev_id;
	pl->con_id = con_id;
	pl->phy = phy;

	mutex_lock(&phy_provider_mutex);
	list_add_tail(&pl->node, &phys);
	mutex_unlock(&phy_provider_mutex);

	return 0;
}