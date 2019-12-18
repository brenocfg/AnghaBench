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
 scalar_t__ DestNone ; 
 scalar_t__ DestRemote ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ whereToSendOutput ; 

__attribute__((used)) static void
WalSndShutdown(void)
{
	/*
	 * Reset whereToSendOutput to prevent ereport from attempting to send any
	 * more messages to the standby.
	 */
	if (whereToSendOutput == DestRemote)
		whereToSendOutput = DestNone;

	proc_exit(0);
	abort();					/* keep the compiler quiet */
}