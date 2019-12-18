#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct btrfsic_block_link_hashtable {scalar_t__ table; } ;
struct btrfsic_block_link {int /*<<< orphan*/  collision_resolving_node; TYPE_4__* block_ref_from; TYPE_3__* block_ref_to; } ;
struct TYPE_8__ {int dev_bytenr; TYPE_2__* dev_state; } ;
struct TYPE_7__ {int dev_bytenr; TYPE_1__* dev_state; } ;
struct TYPE_6__ {scalar_t__ bdev; } ;
struct TYPE_5__ {scalar_t__ bdev; } ;

/* Variables and functions */
 int BTRFSIC_BLOCK_LINK_HASHTABLE_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void btrfsic_block_link_hashtable_add(
		struct btrfsic_block_link *l,
		struct btrfsic_block_link_hashtable *h)
{
	const unsigned int hashval =
	    (((unsigned int)(l->block_ref_to->dev_bytenr >> 16)) ^
	     ((unsigned int)(l->block_ref_from->dev_bytenr >> 16)) ^
	     ((unsigned int)((uintptr_t)l->block_ref_to->dev_state->bdev)) ^
	     ((unsigned int)((uintptr_t)l->block_ref_from->dev_state->bdev)))
	     & (BTRFSIC_BLOCK_LINK_HASHTABLE_SIZE - 1);

	BUG_ON(NULL == l->block_ref_to);
	BUG_ON(NULL == l->block_ref_from);
	list_add(&l->collision_resolving_node, h->table + hashval);
}