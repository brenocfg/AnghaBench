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
struct wimax_dev {int state; int /*<<< orphan*/  mutex; } ;
typedef  enum wimax_st { ____Placeholder_wimax_st } wimax_st ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

enum wimax_st wimax_state_get(struct wimax_dev *wimax_dev)
{
	enum wimax_st state;
	mutex_lock(&wimax_dev->mutex);
	state = wimax_dev->state;
	mutex_unlock(&wimax_dev->mutex);
	return state;
}