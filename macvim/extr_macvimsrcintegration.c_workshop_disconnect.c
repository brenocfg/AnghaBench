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
 int /*<<< orphan*/  XtRemoveInput (scalar_t__) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ inputHandler ; 
 int sd ; 

void	workshop_disconnect()
{
	/* Probably need to send some message here */

	/*
	 * socket closed on other end
	 */
	XtRemoveInput(inputHandler);
	close(sd);
	inputHandler = 0;
	sd = -1;

}