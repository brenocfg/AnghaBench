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
struct net_device {int dummy; } ;
struct flow_indr_block_dev {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  ht_node; struct net_device* dev; int /*<<< orphan*/  cb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct flow_indr_block_dev* flow_indr_block_dev_lookup (struct net_device*) ; 
 int /*<<< orphan*/  flow_indr_setup_block_ht_params ; 
 int /*<<< orphan*/  indr_setup_block_ht ; 
 int /*<<< orphan*/  kfree (struct flow_indr_block_dev*) ; 
 struct flow_indr_block_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct flow_indr_block_dev *
flow_indr_block_dev_get(struct net_device *dev)
{
	struct flow_indr_block_dev *indr_dev;

	indr_dev = flow_indr_block_dev_lookup(dev);
	if (indr_dev)
		goto inc_ref;

	indr_dev = kzalloc(sizeof(*indr_dev), GFP_KERNEL);
	if (!indr_dev)
		return NULL;

	INIT_LIST_HEAD(&indr_dev->cb_list);
	indr_dev->dev = dev;
	if (rhashtable_insert_fast(&indr_setup_block_ht, &indr_dev->ht_node,
				   flow_indr_setup_block_ht_params)) {
		kfree(indr_dev);
		return NULL;
	}

inc_ref:
	indr_dev->refcnt++;
	return indr_dev;
}