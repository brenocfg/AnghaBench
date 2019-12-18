#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_pwork_work_fn ;
struct xfs_pwork_ctl {int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  nr_work; struct xfs_mount* mp; scalar_t__ error; int /*<<< orphan*/  work_fn; int /*<<< orphan*/  wq; } ;
struct xfs_mount {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {unsigned int pwork_threads; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WQ_FREEZABLE ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,unsigned int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_pwork_init (struct xfs_mount*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__ xfs_globals ; 

int
xfs_pwork_init(
	struct xfs_mount	*mp,
	struct xfs_pwork_ctl	*pctl,
	xfs_pwork_work_fn	work_fn,
	const char		*tag,
	unsigned int		nr_threads)
{
#ifdef DEBUG
	if (xfs_globals.pwork_threads >= 0)
		nr_threads = xfs_globals.pwork_threads;
#endif
	trace_xfs_pwork_init(mp, nr_threads, current->pid);

	pctl->wq = alloc_workqueue("%s-%d", WQ_FREEZABLE, nr_threads, tag,
			current->pid);
	if (!pctl->wq)
		return -ENOMEM;
	pctl->work_fn = work_fn;
	pctl->error = 0;
	pctl->mp = mp;
	atomic_set(&pctl->nr_work, 0);
	init_waitqueue_head(&pctl->poll_wait);

	return 0;
}