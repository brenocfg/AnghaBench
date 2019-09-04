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
struct f_ecm {int /*<<< orphan*/  notify_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECM_NOTIFY_CONNECT ; 
 int /*<<< orphan*/  ecm_do_notify (struct f_ecm*) ; 

__attribute__((used)) static void ecm_notify(struct f_ecm *ecm)
{
	/* NOTE on most versions of Linux, host side cdc-ethernet
	 * won't listen for notifications until its netdevice opens.
	 * The first notification then sits in the FIFO for a long
	 * time, and the second one is queued.
	 */
	ecm->notify_state = ECM_NOTIFY_CONNECT;
	ecm_do_notify(ecm);
}