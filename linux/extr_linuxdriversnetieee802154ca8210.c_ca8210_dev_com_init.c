#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ca8210_priv {TYPE_1__* spi; void* irq_workqueue; void* mlme_workqueue; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WQ_UNBOUND ; 
 void* alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ca8210_dev_com_init(struct ca8210_priv *priv)
{
	priv->mlme_workqueue = alloc_ordered_workqueue(
		"MLME work queue",
		WQ_UNBOUND
	);
	if (!priv->mlme_workqueue) {
		dev_crit(&priv->spi->dev, "alloc of mlme_workqueue failed!\n");
		return -ENOMEM;
	}

	priv->irq_workqueue = alloc_ordered_workqueue(
		"ca8210 irq worker",
		WQ_UNBOUND
	);
	if (!priv->irq_workqueue) {
		dev_crit(&priv->spi->dev, "alloc of irq_workqueue failed!\n");
		return -ENOMEM;
	}

	return 0;
}