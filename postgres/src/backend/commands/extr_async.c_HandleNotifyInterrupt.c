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

/* Variables and functions */
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ ) ; 
 int notifyInterruptPending ; 

void
HandleNotifyInterrupt(void)
{
	/*
	 * Note: this is called by a SIGNAL HANDLER. You must be very wary what
	 * you do here.
	 */

	/* signal that work needs to be done */
	notifyInterruptPending = true;

	/* make sure the event is processed in due course */
	SetLatch(MyLatch);
}