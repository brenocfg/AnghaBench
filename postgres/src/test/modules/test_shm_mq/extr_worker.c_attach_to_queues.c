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
typedef  int /*<<< orphan*/  shm_toc ;
typedef  int /*<<< orphan*/  shm_mq_handle ;
typedef  int /*<<< orphan*/  shm_mq ;
typedef  int /*<<< orphan*/  dsm_segment ;

/* Variables and functions */
 int /*<<< orphan*/  MyProc ; 
 int /*<<< orphan*/ * shm_mq_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_mq_set_receiver (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_mq_set_sender (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shm_toc_lookup (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
attach_to_queues(dsm_segment *seg, shm_toc *toc, int myworkernumber,
				 shm_mq_handle **inqhp, shm_mq_handle **outqhp)
{
	shm_mq	   *inq;
	shm_mq	   *outq;

	inq = shm_toc_lookup(toc, myworkernumber, false);
	shm_mq_set_receiver(inq, MyProc);
	*inqhp = shm_mq_attach(inq, seg, NULL);
	outq = shm_toc_lookup(toc, myworkernumber + 1, false);
	shm_mq_set_sender(outq, MyProc);
	*outqhp = shm_mq_attach(outq, seg, NULL);
}