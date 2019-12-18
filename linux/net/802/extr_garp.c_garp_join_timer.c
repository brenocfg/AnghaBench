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
struct garp_applicant {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GARP_EVENT_TRANSMIT_PDU ; 
 struct garp_applicant* app ; 
 struct garp_applicant* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garp_gid_event (struct garp_applicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garp_join_timer_arm (struct garp_applicant*) ; 
 int /*<<< orphan*/  garp_pdu_queue (struct garp_applicant*) ; 
 int /*<<< orphan*/  garp_queue_xmit (struct garp_applicant*) ; 
 int /*<<< orphan*/  join_timer ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void garp_join_timer(struct timer_list *t)
{
	struct garp_applicant *app = from_timer(app, t, join_timer);

	spin_lock(&app->lock);
	garp_gid_event(app, GARP_EVENT_TRANSMIT_PDU);
	garp_pdu_queue(app);
	spin_unlock(&app->lock);

	garp_queue_xmit(app);
	garp_join_timer_arm(app);
}