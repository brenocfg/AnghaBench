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
struct TYPE_2__ {scalar_t__ rw_sem; } ;
struct super_block {TYPE_1__ s_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  percpu_down_read (scalar_t__) ; 
 int percpu_down_read_trylock (scalar_t__) ; 
 scalar_t__ percpu_rwsem_is_held (scalar_t__) ; 

int __sb_start_write(struct super_block *sb, int level, bool wait)
{
	bool force_trylock = false;
	int ret = 1;

#ifdef CONFIG_LOCKDEP
	/*
	 * We want lockdep to tell us about possible deadlocks with freezing
	 * but it's it bit tricky to properly instrument it. Getting a freeze
	 * protection works as getting a read lock but there are subtle
	 * problems. XFS for example gets freeze protection on internal level
	 * twice in some cases, which is OK only because we already hold a
	 * freeze protection also on higher level. Due to these cases we have
	 * to use wait == F (trylock mode) which must not fail.
	 */
	if (wait) {
		int i;

		for (i = 0; i < level - 1; i++)
			if (percpu_rwsem_is_held(sb->s_writers.rw_sem + i)) {
				force_trylock = true;
				break;
			}
	}
#endif
	if (wait && !force_trylock)
		percpu_down_read(sb->s_writers.rw_sem + level-1);
	else
		ret = percpu_down_read_trylock(sb->s_writers.rw_sem + level-1);

	WARN_ON(force_trylock && !ret);
	return ret;
}