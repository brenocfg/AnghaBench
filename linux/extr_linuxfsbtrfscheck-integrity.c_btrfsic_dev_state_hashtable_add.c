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
struct btrfsic_dev_state_hashtable {scalar_t__ table; } ;
struct btrfsic_dev_state {int /*<<< orphan*/  collision_resolving_node; TYPE_1__* bdev; } ;
struct TYPE_2__ {scalar_t__ bd_dev; } ;

/* Variables and functions */
 int BTRFSIC_DEV2STATE_HASHTABLE_SIZE ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void btrfsic_dev_state_hashtable_add(
		struct btrfsic_dev_state *ds,
		struct btrfsic_dev_state_hashtable *h)
{
	const unsigned int hashval =
	    (((unsigned int)((uintptr_t)ds->bdev->bd_dev)) &
	     (BTRFSIC_DEV2STATE_HASHTABLE_SIZE - 1));

	list_add(&ds->collision_resolving_node, h->table + hashval);
}