#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* ropt; } ;
struct TYPE_7__ {scalar_t__ blobCount; TYPE_4__ public; scalar_t__ connection; } ;
struct TYPE_6__ {int /*<<< orphan*/  single_txn; } ;
typedef  TYPE_1__ RestoreOptions ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  StartTransaction (TYPE_4__*) ; 
 int /*<<< orphan*/  ahprintf (TYPE_2__*,char*) ; 

void
StartRestoreBlobs(ArchiveHandle *AH)
{
	RestoreOptions *ropt = AH->public.ropt;

	if (!ropt->single_txn)
	{
		if (AH->connection)
			StartTransaction(&AH->public);
		else
			ahprintf(AH, "BEGIN;\n\n");
	}

	AH->blobCount = 0;
}