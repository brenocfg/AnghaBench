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
struct tsi721_device {int /*<<< orphan*/ * idb_base; int /*<<< orphan*/  idb_dma; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IDB_QSIZE ; 
 int TSI721_IDB_ENTRY_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi721_doorbell_free(struct tsi721_device *priv)
{
	if (priv->idb_base == NULL)
		return;

	/* Free buffer allocated for inbound doorbell queue */
	dma_free_coherent(&priv->pdev->dev, IDB_QSIZE * TSI721_IDB_ENTRY_SIZE,
			  priv->idb_base, priv->idb_dma);
	priv->idb_base = NULL;
}