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
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 struct workqueue_struct* alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 struct workqueue_struct* nfsiod_workqueue ; 

__attribute__((used)) static int nfsiod_start(void)
{
	struct workqueue_struct *wq;
	dprintk("RPC:       creating workqueue nfsiod\n");
	wq = alloc_workqueue("nfsiod", WQ_MEM_RECLAIM, 0);
	if (wq == NULL)
		return -ENOMEM;
	nfsiod_workqueue = wq;
	return 0;
}