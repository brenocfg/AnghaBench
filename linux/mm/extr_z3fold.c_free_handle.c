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
struct z3fold_buddy_slots {scalar_t__* slot; } ;

/* Variables and functions */
 int BUDDY_MASK ; 
 int PAGE_HEADLESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct z3fold_buddy_slots* handle_to_slots (unsigned long) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct z3fold_buddy_slots*) ; 
 struct z3fold_pool* slots_to_pool (struct z3fold_buddy_slots*) ; 

__attribute__((used)) static inline void free_handle(unsigned long handle)
{
	struct z3fold_buddy_slots *slots;
	int i;
	bool is_free;

	if (handle & (1 << PAGE_HEADLESS))
		return;

	WARN_ON(*(unsigned long *)handle == 0);
	*(unsigned long *)handle = 0;
	slots = handle_to_slots(handle);
	is_free = true;
	for (i = 0; i <= BUDDY_MASK; i++) {
		if (slots->slot[i]) {
			is_free = false;
			break;
		}
	}

	if (is_free) {
		struct z3fold_pool *pool = slots_to_pool(slots);

		kmem_cache_free(pool->c_handle, slots);
	}
}