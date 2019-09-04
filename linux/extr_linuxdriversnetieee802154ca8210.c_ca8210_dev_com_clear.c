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
struct ca8210_priv {int /*<<< orphan*/  irq_workqueue; int /*<<< orphan*/  mlme_workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca8210_dev_com_clear(struct ca8210_priv *priv)
{
	flush_workqueue(priv->mlme_workqueue);
	destroy_workqueue(priv->mlme_workqueue);
	flush_workqueue(priv->irq_workqueue);
	destroy_workqueue(priv->irq_workqueue);
}