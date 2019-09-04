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
struct cw1200_common {int /*<<< orphan*/  bh_wq; int /*<<< orphan*/  bh_tx; scalar_t__ bh_error; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void cw1200_bh_wakeup(struct cw1200_common *priv)
{
	pr_debug("[BH] wakeup.\n");
	if (priv->bh_error) {
		pr_err("[BH] wakeup failed (BH error)\n");
		return;
	}

	if (atomic_add_return(1, &priv->bh_tx) == 1)
		wake_up(&priv->bh_wq);
}