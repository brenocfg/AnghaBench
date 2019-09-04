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
struct fnic {int /*<<< orphan*/  notify_timer; } ;

/* Variables and functions */
 scalar_t__ FNIC_NOTIFY_TIMER_PERIOD ; 
 struct fnic* fnic ; 
 int /*<<< orphan*/  fnic_handle_link_event (struct fnic*) ; 
 struct fnic* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_timer ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 

__attribute__((used)) static void fnic_notify_timer(struct timer_list *t)
{
	struct fnic *fnic = from_timer(fnic, t, notify_timer);

	fnic_handle_link_event(fnic);
	mod_timer(&fnic->notify_timer,
		  round_jiffies(jiffies + FNIC_NOTIFY_TIMER_PERIOD));
}