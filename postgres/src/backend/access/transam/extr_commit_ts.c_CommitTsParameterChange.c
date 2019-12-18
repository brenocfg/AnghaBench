#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ commitTsActive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateCommitTs () ; 
 int /*<<< orphan*/  DeactivateCommitTs () ; 
 TYPE_1__* commitTsShared ; 

void
CommitTsParameterChange(bool newvalue, bool oldvalue)
{
	/*
	 * If the commit_ts module is disabled in this server and we get word from
	 * the master server that it is enabled there, activate it so that we can
	 * replay future WAL records involving it; also mark it as active on
	 * pg_control.  If the old value was already set, we already did this, so
	 * don't do anything.
	 *
	 * If the module is disabled in the master, disable it here too, unless
	 * the module is enabled locally.
	 *
	 * Note this only runs in the recovery process, so an unlocked read is
	 * fine.
	 */
	if (newvalue)
	{
		if (!commitTsShared->commitTsActive)
			ActivateCommitTs();
	}
	else if (commitTsShared->commitTsActive)
		DeactivateCommitTs();
}