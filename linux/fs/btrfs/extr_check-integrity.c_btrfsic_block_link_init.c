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
struct btrfsic_block_link {int ref_cnt; int /*<<< orphan*/ * block_ref_from; int /*<<< orphan*/ * block_ref_to; int /*<<< orphan*/  collision_resolving_node; int /*<<< orphan*/  node_ref_from; int /*<<< orphan*/  node_ref_to; int /*<<< orphan*/  magic_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFSIC_BLOCK_LINK_MAGIC_NUMBER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfsic_block_link_init(struct btrfsic_block_link *l)
{
	l->magic_num = BTRFSIC_BLOCK_LINK_MAGIC_NUMBER;
	l->ref_cnt = 1;
	INIT_LIST_HEAD(&l->node_ref_to);
	INIT_LIST_HEAD(&l->node_ref_from);
	INIT_LIST_HEAD(&l->collision_resolving_node);
	l->block_ref_to = NULL;
	l->block_ref_from = NULL;
}