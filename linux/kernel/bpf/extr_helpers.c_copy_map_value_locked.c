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
struct bpf_map {int spin_lock_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  ____bpf_spin_lock (struct bpf_spin_lock*) ; 
 int /*<<< orphan*/  ____bpf_spin_unlock (struct bpf_spin_lock*) ; 
 int /*<<< orphan*/  copy_map_value (struct bpf_map*,void*,void*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void copy_map_value_locked(struct bpf_map *map, void *dst, void *src,
			   bool lock_src)
{
	struct bpf_spin_lock *lock;

	if (lock_src)
		lock = src + map->spin_lock_off;
	else
		lock = dst + map->spin_lock_off;
	preempt_disable();
	____bpf_spin_lock(lock);
	copy_map_value(map, dst, src);
	____bpf_spin_unlock(lock);
	preempt_enable();
}