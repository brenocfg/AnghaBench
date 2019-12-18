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
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 struct workqueue_struct* nfsiod_workqueue ; 

__attribute__((used)) static void nfsiod_stop(void)
{
	struct workqueue_struct *wq;

	wq = nfsiod_workqueue;
	if (wq == NULL)
		return;
	nfsiod_workqueue = NULL;
	destroy_workqueue(wq);
}