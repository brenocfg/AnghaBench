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
struct z3fold_pool {int /*<<< orphan*/  c_handle; } ;
struct z3fold_buddy_slots {unsigned long pool; int /*<<< orphan*/  slot; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_HIGHMEM ; 
 int __GFP_MOVABLE ; 
 struct z3fold_buddy_slots* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct z3fold_buddy_slots *alloc_slots(struct z3fold_pool *pool,
							gfp_t gfp)
{
	struct z3fold_buddy_slots *slots;

	slots = kmem_cache_alloc(pool->c_handle,
				 (gfp & ~(__GFP_HIGHMEM | __GFP_MOVABLE)));

	if (slots) {
		memset(slots->slot, 0, sizeof(slots->slot));
		slots->pool = (unsigned long)pool;
	}

	return slots;
}