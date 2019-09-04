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
struct TYPE_2__ {int /*<<< orphan*/  dfs_tasklet; } ;
struct mt76x2_dev {int /*<<< orphan*/  pre_tbtt_tasklet; TYPE_1__ dfs_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x2_dma_cleanup (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_mcu_cleanup (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_stop_hardware (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

void mt76x2_cleanup(struct mt76x2_dev *dev)
{
	tasklet_disable(&dev->dfs_pd.dfs_tasklet);
	tasklet_disable(&dev->pre_tbtt_tasklet);
	mt76x2_stop_hardware(dev);
	mt76x2_dma_cleanup(dev);
	mt76x2_mcu_cleanup(dev);
}