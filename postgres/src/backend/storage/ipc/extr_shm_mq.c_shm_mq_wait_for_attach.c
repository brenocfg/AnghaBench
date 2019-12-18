#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shm_mq_result ;
struct TYPE_7__ {int /*<<< orphan*/  mqh_handle; TYPE_2__* mqh_queue; } ;
typedef  TYPE_1__ shm_mq_handle ;
struct TYPE_8__ {int /*<<< orphan*/ * mq_receiver; int /*<<< orphan*/ * mq_sender; } ;
typedef  TYPE_2__ shm_mq ;
typedef  int /*<<< orphan*/  PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MyProc ; 
 int /*<<< orphan*/  SHM_MQ_DETACHED ; 
 int /*<<< orphan*/  SHM_MQ_SUCCESS ; 
 scalar_t__ shm_mq_get_receiver (TYPE_2__*) ; 
 scalar_t__ shm_mq_get_sender (TYPE_2__*) ; 
 scalar_t__ shm_mq_wait_internal (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

shm_mq_result
shm_mq_wait_for_attach(shm_mq_handle *mqh)
{
	shm_mq	   *mq = mqh->mqh_queue;
	PGPROC	  **victim;

	if (shm_mq_get_receiver(mq) == MyProc)
		victim = &mq->mq_sender;
	else
	{
		Assert(shm_mq_get_sender(mq) == MyProc);
		victim = &mq->mq_receiver;
	}

	if (shm_mq_wait_internal(mq, victim, mqh->mqh_handle))
		return SHM_MQ_SUCCESS;
	else
		return SHM_MQ_DETACHED;
}