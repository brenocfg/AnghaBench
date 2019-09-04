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
struct cw1200_common {int /*<<< orphan*/  bh_work; int /*<<< orphan*/  bh_workqueue; int /*<<< orphan*/  bh_evt_wq; int /*<<< orphan*/  bh_wq; scalar_t__ buf_id_rx; scalar_t__ buf_id_tx; scalar_t__ hw_bufs_used; scalar_t__ bh_error; int /*<<< orphan*/  bh_suspend; int /*<<< orphan*/  bh_term; int /*<<< orphan*/  bh_tx; int /*<<< orphan*/  bh_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CW1200_BH_RESUMED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WQ_CPU_INTENSIVE ; 
 int WQ_HIGHPRI ; 
 int WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_bh_work ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cw1200_register_bh(struct cw1200_common *priv)
{
	int err = 0;
	/* Realtime workqueue */
	priv->bh_workqueue = alloc_workqueue("cw1200_bh",
				WQ_MEM_RECLAIM | WQ_HIGHPRI
				| WQ_CPU_INTENSIVE, 1);

	if (!priv->bh_workqueue)
		return -ENOMEM;

	INIT_WORK(&priv->bh_work, cw1200_bh_work);

	pr_debug("[BH] register.\n");

	atomic_set(&priv->bh_rx, 0);
	atomic_set(&priv->bh_tx, 0);
	atomic_set(&priv->bh_term, 0);
	atomic_set(&priv->bh_suspend, CW1200_BH_RESUMED);
	priv->bh_error = 0;
	priv->hw_bufs_used = 0;
	priv->buf_id_tx = 0;
	priv->buf_id_rx = 0;
	init_waitqueue_head(&priv->bh_wq);
	init_waitqueue_head(&priv->bh_evt_wq);

	err = !queue_work(priv->bh_workqueue, &priv->bh_work);
	WARN_ON(err);
	return err;
}