#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ropt; int /*<<< orphan*/ * dopt; } ;
typedef  int /*<<< orphan*/  RestoreOptions ;
typedef  int /*<<< orphan*/  DumpOptions ;
typedef  TYPE_1__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * dumpOptionsFromRestoreOptions (int /*<<< orphan*/ *) ; 

void
SetArchiveOptions(Archive *AH, DumpOptions *dopt, RestoreOptions *ropt)
{
	/* Caller can omit dump options, in which case we synthesize them */
	if (dopt == NULL && ropt != NULL)
		dopt = dumpOptionsFromRestoreOptions(ropt);

	/* Save options for later access */
	AH->dopt = dopt;
	AH->ropt = ropt;
}