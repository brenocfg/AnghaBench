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
struct xfs_pwork_ctl {int /*<<< orphan*/  wq; int /*<<< orphan*/  nr_work; } ;
struct xfs_pwork {int /*<<< orphan*/  work; struct xfs_pwork_ctl* pctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_pwork_work ; 

void
xfs_pwork_queue(
	struct xfs_pwork_ctl	*pctl,
	struct xfs_pwork	*pwork)
{
	INIT_WORK(&pwork->work, xfs_pwork_work);
	pwork->pctl = pctl;
	atomic_inc(&pctl->nr_work);
	queue_work(pctl->wq, &pwork->work);
}