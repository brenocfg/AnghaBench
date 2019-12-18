#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  xcnt; } ;
typedef  TYPE_1__* Snapshot ;
typedef  int /*<<< orphan*/  SnapBuild ;

/* Variables and functions */
 scalar_t__ CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 int ExportInProgress ; 
 char* ExportSnapshot (TYPE_1__*) ; 
 scalar_t__ IsTransactionOrTransactionBlock () ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ SavedResourceOwnerDuringExport ; 
 TYPE_1__* SnapBuildInitialSnapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  XACT_REPEATABLE_READ ; 
 int /*<<< orphan*/  XactIsoLevel ; 
 int XactReadOnly ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_plural (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

const char *
SnapBuildExportSnapshot(SnapBuild *builder)
{
	Snapshot	snap;
	char	   *snapname;

	if (IsTransactionOrTransactionBlock())
		elog(ERROR, "cannot export a snapshot from within a transaction");

	if (SavedResourceOwnerDuringExport)
		elog(ERROR, "can only export one snapshot at a time");

	SavedResourceOwnerDuringExport = CurrentResourceOwner;
	ExportInProgress = true;

	StartTransactionCommand();

	/* There doesn't seem to a nice API to set these */
	XactIsoLevel = XACT_REPEATABLE_READ;
	XactReadOnly = true;

	snap = SnapBuildInitialSnapshot(builder);

	/*
	 * now that we've built a plain snapshot, make it active and use the
	 * normal mechanisms for exporting it
	 */
	snapname = ExportSnapshot(snap);

	ereport(LOG,
			(errmsg_plural("exported logical decoding snapshot: \"%s\" with %u transaction ID",
						   "exported logical decoding snapshot: \"%s\" with %u transaction IDs",
						   snap->xcnt,
						   snapname, snap->xcnt)));
	return snapname;
}