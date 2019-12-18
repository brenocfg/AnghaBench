#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* shared; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  currentWorker; } ;
typedef  TYPE_2__ Sharedsort ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WORKER (TYPE_1__*) ; 

__attribute__((used)) static int
worker_get_identifier(Tuplesortstate *state)
{
	Sharedsort *shared = state->shared;
	int			worker;

	Assert(WORKER(state));

	SpinLockAcquire(&shared->mutex);
	worker = shared->currentWorker++;
	SpinLockRelease(&shared->mutex);

	return worker;
}