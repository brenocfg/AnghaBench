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
struct mt76x2_dev {int /*<<< orphan*/  mt76; int /*<<< orphan*/  tx_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_dma_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void mt76x2_dma_cleanup(struct mt76x2_dev *dev)
{
	tasklet_kill(&dev->tx_tasklet);
	mt76_dma_cleanup(&dev->mt76);
}