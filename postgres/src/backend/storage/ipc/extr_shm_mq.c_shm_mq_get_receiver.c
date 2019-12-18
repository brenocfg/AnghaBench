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
struct TYPE_3__ {int /*<<< orphan*/  mq_mutex; int /*<<< orphan*/ * mq_receiver; } ;
typedef  TYPE_1__ shm_mq ;
typedef  int /*<<< orphan*/  PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 

PGPROC *
shm_mq_get_receiver(shm_mq *mq)
{
	PGPROC	   *receiver;

	SpinLockAcquire(&mq->mq_mutex);
	receiver = mq->mq_receiver;
	SpinLockRelease(&mq->mq_mutex);

	return receiver;
}