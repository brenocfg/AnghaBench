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
typedef  int /*<<< orphan*/  VirtualTransactionId ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/ * GetConflictingVirtualXIDs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  PROCSIG_RECOVERY_CONFLICT_TABLESPACE ; 
 int /*<<< orphan*/  ResolveRecoveryConflictWithVirtualXIDs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ResolveRecoveryConflictWithTablespace(Oid tsid)
{
	VirtualTransactionId *temp_file_users;

	/*
	 * Standby users may be currently using this tablespace for their
	 * temporary files. We only care about current users because
	 * temp_tablespace parameter will just ignore tablespaces that no longer
	 * exist.
	 *
	 * Ask everybody to cancel their queries immediately so we can ensure no
	 * temp files remain and we can remove the tablespace. Nuke the entire
	 * site from orbit, it's the only way to be sure.
	 *
	 * XXX: We could work out the pids of active backends using this
	 * tablespace by examining the temp filenames in the directory. We would
	 * then convert the pids into VirtualXIDs before attempting to cancel
	 * them.
	 *
	 * We don't wait for commit because drop tablespace is non-transactional.
	 */
	temp_file_users = GetConflictingVirtualXIDs(InvalidTransactionId,
												InvalidOid);
	ResolveRecoveryConflictWithVirtualXIDs(temp_file_users,
										   PROCSIG_RECOVERY_CONFLICT_TABLESPACE);
}