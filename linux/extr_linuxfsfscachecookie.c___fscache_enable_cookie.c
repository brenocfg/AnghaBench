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
struct fscache_cookie {scalar_t__ type; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE_COOKIE_ENABLED ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_ENABLEMENT_LOCK ; 
 scalar_t__ FSCACHE_COOKIE_TYPE_INDEX ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __fscache_wait_on_invalidate (struct fscache_cookie*) ; 
 int /*<<< orphan*/  _enter (char*,struct fscache_cookie*) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fscache_acquire_non_index_cookie (struct fscache_cookie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_update_aux (struct fscache_cookie*,void const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_fscache_enable (struct fscache_cookie*) ; 
 int /*<<< orphan*/  wait_on_bit_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __fscache_enable_cookie(struct fscache_cookie *cookie,
			     const void *aux_data,
			     loff_t object_size,
			     bool (*can_enable)(void *data),
			     void *data)
{
	_enter("%p", cookie);

	trace_fscache_enable(cookie);

	wait_on_bit_lock(&cookie->flags, FSCACHE_COOKIE_ENABLEMENT_LOCK,
			 TASK_UNINTERRUPTIBLE);

	fscache_update_aux(cookie, aux_data);

	if (test_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags))
		goto out_unlock;

	if (can_enable && !can_enable(data)) {
		/* The netfs decided it didn't want to enable after all */
	} else if (cookie->type != FSCACHE_COOKIE_TYPE_INDEX) {
		/* Wait for outstanding disablement to complete */
		__fscache_wait_on_invalidate(cookie);

		if (fscache_acquire_non_index_cookie(cookie, object_size) == 0)
			set_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags);
	} else {
		set_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags);
	}

out_unlock:
	clear_bit_unlock(FSCACHE_COOKIE_ENABLEMENT_LOCK, &cookie->flags);
	wake_up_bit(&cookie->flags, FSCACHE_COOKIE_ENABLEMENT_LOCK);
}