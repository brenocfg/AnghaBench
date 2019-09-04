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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int HP_NUM_WORDS ; 
 int /*<<< orphan*/  __frame_ptr ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_dma ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 TYPE_1__* pcfg ; 

__attribute__((used)) static void deallocate_frame_data(void)
{
	dma_unmap_single(pcfg->dev, frame_dma, 4 * HP_NUM_WORDS,
			 DMA_BIDIRECTIONAL);
	kfree(__frame_ptr);
}