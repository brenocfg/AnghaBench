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
struct mutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 scalar_t__ likely (int) ; 
 int mutex_lock_killable (struct mutex*) ; 
 int mutex_lock_killable_nested (struct mutex*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  swap (struct mutex*,struct mutex*) ; 

__attribute__((used)) static int kcmp_lock(struct mutex *m1, struct mutex *m2)
{
	int err;

	if (m2 > m1)
		swap(m1, m2);

	err = mutex_lock_killable(m1);
	if (!err && likely(m1 != m2)) {
		err = mutex_lock_killable_nested(m2, SINGLE_DEPTH_NESTING);
		if (err)
			mutex_unlock(m1);
	}

	return err;
}