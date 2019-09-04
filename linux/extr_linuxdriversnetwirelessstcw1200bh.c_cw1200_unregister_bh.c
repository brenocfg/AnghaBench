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
struct cw1200_common {int /*<<< orphan*/ * bh_workqueue; int /*<<< orphan*/  bh_wq; int /*<<< orphan*/  bh_term; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void cw1200_unregister_bh(struct cw1200_common *priv)
{
	atomic_add(1, &priv->bh_term);
	wake_up(&priv->bh_wq);

	flush_workqueue(priv->bh_workqueue);

	destroy_workqueue(priv->bh_workqueue);
	priv->bh_workqueue = NULL;

	pr_debug("[BH] unregistered.\n");
}