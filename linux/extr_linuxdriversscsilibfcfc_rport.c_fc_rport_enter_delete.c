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
struct fc_rport_priv {scalar_t__ rp_state; scalar_t__ event; int /*<<< orphan*/  kref; int /*<<< orphan*/  event_work; int /*<<< orphan*/  rp_mutex; } ;
typedef  enum fc_rport_event { ____Placeholder_fc_rport_event } fc_rport_event ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*) ; 
 scalar_t__ RPORT_EV_NONE ; 
 scalar_t__ RPORT_ST_DELETE ; 
 int /*<<< orphan*/  fc_rport_destroy ; 
 int /*<<< orphan*/  fc_rport_state_enter (struct fc_rport_priv*,scalar_t__) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rport_event_queue ; 

__attribute__((used)) static void fc_rport_enter_delete(struct fc_rport_priv *rdata,
				  enum fc_rport_event event)
{
	lockdep_assert_held(&rdata->rp_mutex);

	if (rdata->rp_state == RPORT_ST_DELETE)
		return;

	FC_RPORT_DBG(rdata, "Delete port\n");

	fc_rport_state_enter(rdata, RPORT_ST_DELETE);

	kref_get(&rdata->kref);
	if (rdata->event == RPORT_EV_NONE &&
	    !queue_work(rport_event_queue, &rdata->event_work))
		kref_put(&rdata->kref, fc_rport_destroy);

	rdata->event = event;
}