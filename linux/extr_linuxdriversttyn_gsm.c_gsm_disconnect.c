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
struct gsm_mux {int /*<<< orphan*/  event; int /*<<< orphan*/  t2_timer; struct gsm_dlci** dlci; } ;
struct gsm_dlci {scalar_t__ state; } ;
struct gsm_control {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CLD ; 
 scalar_t__ DLCI_CLOSED ; 
 int EINTR ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct gsm_control* gsm_control_send (struct gsm_mux*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsm_control_wait (struct gsm_mux*,struct gsm_control*) ; 
 int /*<<< orphan*/  gsm_dlci_begin_close (struct gsm_dlci*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gsm_disconnect(struct gsm_mux *gsm)
{
	struct gsm_dlci *dlci = gsm->dlci[0];
	struct gsm_control *gc;

	if (!dlci)
		return 0;

	/* In theory disconnecting DLCI 0 is sufficient but for some
	   modems this is apparently not the case. */
	gc = gsm_control_send(gsm, CMD_CLD, NULL, 0);
	if (gc)
		gsm_control_wait(gsm, gc);

	del_timer_sync(&gsm->t2_timer);
	/* Now we are sure T2 has stopped */

	gsm_dlci_begin_close(dlci);
	wait_event_interruptible(gsm->event,
				dlci->state == DLCI_CLOSED);

	if (signal_pending(current))
		return -EINTR;

	return 0;
}