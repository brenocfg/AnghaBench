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
typedef  size_t u32 ;
struct arena_info {size_t nfree; TYPE_1__* map_locks; } ;
struct aligned_lock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btt_maplocks_init(struct arena_info *arena)
{
	u32 i;

	arena->map_locks = kcalloc(arena->nfree, sizeof(struct aligned_lock),
				GFP_KERNEL);
	if (!arena->map_locks)
		return -ENOMEM;

	for (i = 0; i < arena->nfree; i++)
		spin_lock_init(&arena->map_locks[i].lock);

	return 0;
}