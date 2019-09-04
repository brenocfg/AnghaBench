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
typedef  int /*<<< orphan*/  raw_spinlock_t ;
typedef  int /*<<< orphan*/  atomic64_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long L1_CACHE_SHIFT ; 
 int NR_LOCKS ; 
 TYPE_1__* atomic64_lock ; 

__attribute__((used)) static inline raw_spinlock_t *lock_addr(const atomic64_t *v)
{
	unsigned long addr = (unsigned long) v;

	addr >>= L1_CACHE_SHIFT;
	addr ^= (addr >> 8) ^ (addr >> 16);
	return &atomic64_lock[addr & (NR_LOCKS - 1)].lock;
}