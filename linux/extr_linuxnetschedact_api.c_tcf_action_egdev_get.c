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
struct tcf_action_net {int /*<<< orphan*/  egdev_ht; } ;
struct tcf_action_egdev {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  ht_node; struct net_device const* dev; int /*<<< orphan*/  cb_list; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (struct net_device const*) ; 
 struct tcf_action_egdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct tcf_action_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_action_egdev_ht_params ; 
 struct tcf_action_egdev* tcf_action_egdev_lookup (struct net_device const*) ; 
 int /*<<< orphan*/  tcf_action_net_id ; 

__attribute__((used)) static struct tcf_action_egdev *
tcf_action_egdev_get(const struct net_device *dev)
{
	struct tcf_action_egdev *egdev;
	struct tcf_action_net *tan;

	egdev = tcf_action_egdev_lookup(dev);
	if (egdev)
		goto inc_ref;

	egdev = kzalloc(sizeof(*egdev), GFP_KERNEL);
	if (!egdev)
		return NULL;
	INIT_LIST_HEAD(&egdev->cb_list);
	egdev->dev = dev;
	tan = net_generic(dev_net(dev), tcf_action_net_id);
	rhashtable_insert_fast(&tan->egdev_ht, &egdev->ht_node,
			       tcf_action_egdev_ht_params);

inc_ref:
	egdev->refcnt++;
	return egdev;
}