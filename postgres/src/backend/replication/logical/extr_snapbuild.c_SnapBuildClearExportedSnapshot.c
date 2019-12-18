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
 int /*<<< orphan*/  AbortCurrentTransaction () ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 int ExportInProgress ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 int /*<<< orphan*/ * SavedResourceOwnerDuringExport ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
SnapBuildClearExportedSnapshot(void)
{
	/* nothing exported, that is the usual case */
	if (!ExportInProgress)
		return;

	if (!IsTransactionState())
		elog(ERROR, "clearing exported snapshot in wrong transaction state");

	/* make sure nothing  could have ever happened */
	AbortCurrentTransaction();

	CurrentResourceOwner = SavedResourceOwnerDuringExport;
	SavedResourceOwnerDuringExport = NULL;
	ExportInProgress = false;
}