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
struct f_ncm {int /*<<< orphan*/  notify_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCM_NOTIFY_SPEED ; 
 int /*<<< orphan*/  ncm_do_notify (struct f_ncm*) ; 

__attribute__((used)) static void ncm_notify(struct f_ncm *ncm)
{
	/*
	 * NOTE on most versions of Linux, host side cdc-ethernet
	 * won't listen for notifications until its netdevice opens.
	 * The first notification then sits in the FIFO for a long
	 * time, and the second one is queued.
	 *
	 * If ncm_notify() is called before the second (CONNECT)
	 * notification is sent, then it will reset to send the SPEED
	 * notificaion again (and again, and again), but it's not a problem
	 */
	ncm->notify_state = NCM_NOTIFY_SPEED;
	ncm_do_notify(ncm);
}