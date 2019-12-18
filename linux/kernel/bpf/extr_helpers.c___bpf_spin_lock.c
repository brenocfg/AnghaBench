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
struct bpf_spin_lock {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  VAL ; 
 int /*<<< orphan*/  atomic_cond_read_relaxed (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void __bpf_spin_lock(struct bpf_spin_lock *lock)
{
	atomic_t *l = (void *)lock;

	BUILD_BUG_ON(sizeof(*l) != sizeof(*lock));
	do {
		atomic_cond_read_relaxed(l, !VAL);
	} while (atomic_xchg(l, 1));
}