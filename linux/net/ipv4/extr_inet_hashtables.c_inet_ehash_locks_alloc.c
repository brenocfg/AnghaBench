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
struct inet_hashinfo {unsigned int ehash_locks_mask; int /*<<< orphan*/ * ehash_locks; scalar_t__ ehash_mask; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int L1_CACHE_BYTES ; 
 int /*<<< orphan*/ * kvmalloc_array (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,scalar_t__) ; 
 unsigned int num_possible_cpus () ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int inet_ehash_locks_alloc(struct inet_hashinfo *hashinfo)
{
	unsigned int locksz = sizeof(spinlock_t);
	unsigned int i, nblocks = 1;

	if (locksz != 0) {
		/* allocate 2 cache lines or at least one spinlock per cpu */
		nblocks = max(2U * L1_CACHE_BYTES / locksz, 1U);
		nblocks = roundup_pow_of_two(nblocks * num_possible_cpus());

		/* no more locks than number of hash buckets */
		nblocks = min(nblocks, hashinfo->ehash_mask + 1);

		hashinfo->ehash_locks = kvmalloc_array(nblocks, locksz, GFP_KERNEL);
		if (!hashinfo->ehash_locks)
			return -ENOMEM;

		for (i = 0; i < nblocks; i++)
			spin_lock_init(&hashinfo->ehash_locks[i]);
	}
	hashinfo->ehash_locks_mask = nblocks - 1;
	return 0;
}