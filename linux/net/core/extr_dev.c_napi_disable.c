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
struct napi_struct {int /*<<< orphan*/  state; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAPI_STATE_DISABLE ; 
 int /*<<< orphan*/  NAPI_STATE_NPSVC ; 
 int /*<<< orphan*/  NAPI_STATE_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void napi_disable(struct napi_struct *n)
{
	might_sleep();
	set_bit(NAPI_STATE_DISABLE, &n->state);

	while (test_and_set_bit(NAPI_STATE_SCHED, &n->state))
		msleep(1);
	while (test_and_set_bit(NAPI_STATE_NPSVC, &n->state))
		msleep(1);

	hrtimer_cancel(&n->timer);

	clear_bit(NAPI_STATE_DISABLE, &n->state);
}