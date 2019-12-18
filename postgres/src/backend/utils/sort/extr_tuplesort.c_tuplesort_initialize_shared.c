#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsm_segment ;
struct TYPE_5__ {int nTapes; TYPE_1__* tapes; int /*<<< orphan*/  fileset; scalar_t__ workersFinished; scalar_t__ currentWorker; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {long firstblocknumber; } ;
typedef  TYPE_2__ Sharedsort ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  SharedFileSetInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 

void
tuplesort_initialize_shared(Sharedsort *shared, int nWorkers, dsm_segment *seg)
{
	int			i;

	Assert(nWorkers > 0);

	SpinLockInit(&shared->mutex);
	shared->currentWorker = 0;
	shared->workersFinished = 0;
	SharedFileSetInit(&shared->fileset, seg);
	shared->nTapes = nWorkers;
	for (i = 0; i < nWorkers; i++)
	{
		shared->tapes[i].firstblocknumber = 0L;
	}
}