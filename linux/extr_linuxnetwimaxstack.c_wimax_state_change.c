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
struct wimax_dev {scalar_t__ state; int /*<<< orphan*/  mutex; } ;
typedef  enum wimax_st { ____Placeholder_wimax_st } wimax_st ;

/* Variables and functions */
 scalar_t__ __WIMAX_ST_NULL ; 
 int /*<<< orphan*/  __wimax_state_change (struct wimax_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void wimax_state_change(struct wimax_dev *wimax_dev, enum wimax_st new_state)
{
	/*
	 * A driver cannot take the wimax_dev out of the
	 * __WIMAX_ST_NULL state unless by calling wimax_dev_add(). If
	 * the wimax_dev's state is still NULL, we ignore any request
	 * to change its state because it means it hasn't been yet
	 * registered.
	 *
	 * There is no need to complain about it, as routines that
	 * call this might be shared from different code paths that
	 * are called before or after wimax_dev_add() has done its
	 * job.
	 */
	mutex_lock(&wimax_dev->mutex);
	if (wimax_dev->state > __WIMAX_ST_NULL)
		__wimax_state_change(wimax_dev, new_state);
	mutex_unlock(&wimax_dev->mutex);
}