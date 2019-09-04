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
struct mt76_dev {int /*<<< orphan*/ * queue_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_dma_ops ; 

int mt76_dma_attach(struct mt76_dev *dev)
{
	dev->queue_ops = &mt76_dma_ops;
	return 0;
}