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
struct TYPE_4__ {int /*<<< orphan*/  is_similar_or_better; int /*<<< orphan*/  cmp; } ;
struct TYPE_3__ {int /*<<< orphan*/  primary_set; int /*<<< orphan*/  update_mac; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; } ;
struct batadv_algo_ops {int /*<<< orphan*/  list; int /*<<< orphan*/  name; TYPE_2__ neigh; TYPE_1__ iface; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 struct batadv_algo_ops* batadv_algo_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_algo_list ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int batadv_algo_register(struct batadv_algo_ops *bat_algo_ops)
{
	struct batadv_algo_ops *bat_algo_ops_tmp;

	bat_algo_ops_tmp = batadv_algo_get(bat_algo_ops->name);
	if (bat_algo_ops_tmp) {
		pr_info("Trying to register already registered routing algorithm: %s\n",
			bat_algo_ops->name);
		return -EEXIST;
	}

	/* all algorithms must implement all ops (for now) */
	if (!bat_algo_ops->iface.enable ||
	    !bat_algo_ops->iface.disable ||
	    !bat_algo_ops->iface.update_mac ||
	    !bat_algo_ops->iface.primary_set ||
	    !bat_algo_ops->neigh.cmp ||
	    !bat_algo_ops->neigh.is_similar_or_better) {
		pr_info("Routing algo '%s' does not implement required ops\n",
			bat_algo_ops->name);
		return -EINVAL;
	}

	INIT_HLIST_NODE(&bat_algo_ops->list);
	hlist_add_head(&bat_algo_ops->list, &batadv_algo_list);

	return 0;
}