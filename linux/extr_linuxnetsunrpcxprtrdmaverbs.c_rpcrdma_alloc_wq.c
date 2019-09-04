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
struct workqueue_struct {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int WQ_HIGHPRI ; 
 int WQ_MEM_RECLAIM ; 
 struct workqueue_struct* alloc_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 struct workqueue_struct* rpcrdma_receive_wq ; 

int
rpcrdma_alloc_wq(void)
{
	struct workqueue_struct *recv_wq;

	recv_wq = alloc_workqueue("xprtrdma_receive",
				  WQ_MEM_RECLAIM | WQ_HIGHPRI,
				  0);
	if (!recv_wq)
		return -ENOMEM;

	rpcrdma_receive_wq = recv_wq;
	return 0;
}