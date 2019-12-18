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
 scalar_t__ AutoVacPID ; 
 scalar_t__ BgWriterPID ; 
 scalar_t__ CheckpointerPID ; 
 scalar_t__ PgArchPID ; 
 scalar_t__ PgStatPID ; 
 int SIGKILL ; 
 int SIGQUIT ; 
 int /*<<< orphan*/  STARTUP_SIGNALED ; 
 int /*<<< orphan*/  SignalChildren (int) ; 
 scalar_t__ StartupPID ; 
 int /*<<< orphan*/  StartupStatus ; 
 scalar_t__ WalReceiverPID ; 
 scalar_t__ WalWriterPID ; 
 int /*<<< orphan*/  signal_child (scalar_t__,int) ; 

__attribute__((used)) static void
TerminateChildren(int signal)
{
	SignalChildren(signal);
	if (StartupPID != 0)
	{
		signal_child(StartupPID, signal);
		if (signal == SIGQUIT || signal == SIGKILL)
			StartupStatus = STARTUP_SIGNALED;
	}
	if (BgWriterPID != 0)
		signal_child(BgWriterPID, signal);
	if (CheckpointerPID != 0)
		signal_child(CheckpointerPID, signal);
	if (WalWriterPID != 0)
		signal_child(WalWriterPID, signal);
	if (WalReceiverPID != 0)
		signal_child(WalReceiverPID, signal);
	if (AutoVacPID != 0)
		signal_child(AutoVacPID, signal);
	if (PgArchPID != 0)
		signal_child(PgArchPID, signal);
	if (PgStatPID != 0)
		signal_child(PgStatPID, signal);
}