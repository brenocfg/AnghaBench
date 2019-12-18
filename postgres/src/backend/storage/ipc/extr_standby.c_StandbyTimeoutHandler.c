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
 int /*<<< orphan*/  PROCSIG_RECOVERY_CONFLICT_BUFFERPIN ; 
 int /*<<< orphan*/  STANDBY_DEADLOCK_TIMEOUT ; 
 int /*<<< orphan*/  SendRecoveryConflictWithBufferPin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_timeout (int /*<<< orphan*/ ,int) ; 

void
StandbyTimeoutHandler(void)
{
	/* forget any pending STANDBY_DEADLOCK_TIMEOUT request */
	disable_timeout(STANDBY_DEADLOCK_TIMEOUT, false);

	SendRecoveryConflictWithBufferPin(PROCSIG_RECOVERY_CONFLICT_BUFFERPIN);
}