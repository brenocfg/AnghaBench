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
struct nilfs_bmap_store {int /*<<< orphan*/  state; int /*<<< orphan*/  last_allocated_ptr; int /*<<< orphan*/  last_allocated_key; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  u_data; } ;
struct nilfs_bmap {int /*<<< orphan*/  b_state; int /*<<< orphan*/  b_last_allocated_ptr; int /*<<< orphan*/  b_last_allocated_key; TYPE_1__ b_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void nilfs_bmap_save(const struct nilfs_bmap *bmap,
		     struct nilfs_bmap_store *store)
{
	memcpy(store->data, bmap->b_u.u_data, sizeof(store->data));
	store->last_allocated_key = bmap->b_last_allocated_key;
	store->last_allocated_ptr = bmap->b_last_allocated_ptr;
	store->state = bmap->b_state;
}