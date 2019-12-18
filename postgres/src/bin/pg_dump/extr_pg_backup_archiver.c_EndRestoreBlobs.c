#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* ropt; } ;
struct TYPE_7__ {int /*<<< orphan*/  blobCount; TYPE_5__ public; scalar_t__ connection; } ;
struct TYPE_6__ {int /*<<< orphan*/  single_txn; } ;
typedef  TYPE_1__ RestoreOptions ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransaction (TYPE_5__*) ; 
 int /*<<< orphan*/  ahprintf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ngettext (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
EndRestoreBlobs(ArchiveHandle *AH)
{
	RestoreOptions *ropt = AH->public.ropt;

	if (!ropt->single_txn)
	{
		if (AH->connection)
			CommitTransaction(&AH->public);
		else
			ahprintf(AH, "COMMIT;\n\n");
	}

	pg_log_info(ngettext("restored %d large object",
						 "restored %d large objects",
						 AH->blobCount),
				AH->blobCount);
}