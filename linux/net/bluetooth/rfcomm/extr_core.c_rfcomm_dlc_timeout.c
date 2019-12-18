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
struct timer_list {int dummy; } ;
struct rfcomm_dlc {int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFCOMM_TIMED_OUT ; 
 struct rfcomm_dlc* d ; 
 struct rfcomm_dlc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_put (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void rfcomm_dlc_timeout(struct timer_list *t)
{
	struct rfcomm_dlc *d = from_timer(d, t, timer);

	BT_DBG("dlc %p state %ld", d, d->state);

	set_bit(RFCOMM_TIMED_OUT, &d->flags);
	rfcomm_dlc_put(d);
	rfcomm_schedule();
}