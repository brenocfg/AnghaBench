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
struct xfs_pwork_ctl {int error; int /*<<< orphan*/ * wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 

int
xfs_pwork_destroy(
	struct xfs_pwork_ctl	*pctl)
{
	destroy_workqueue(pctl->wq);
	pctl->wq = NULL;
	return pctl->error;
}