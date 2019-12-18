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
struct flow_indr_block_dev {int /*<<< orphan*/  ht_node; scalar_t__ refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_indr_setup_block_ht_params ; 
 int /*<<< orphan*/  indr_setup_block_ht ; 
 int /*<<< orphan*/  kfree (struct flow_indr_block_dev*) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flow_indr_block_dev_put(struct flow_indr_block_dev *indr_dev)
{
	if (--indr_dev->refcnt)
		return;

	rhashtable_remove_fast(&indr_setup_block_ht, &indr_dev->ht_node,
			       flow_indr_setup_block_ht_params);
	kfree(indr_dev);
}