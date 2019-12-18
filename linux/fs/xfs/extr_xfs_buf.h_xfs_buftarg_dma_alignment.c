#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_buftarg {TYPE_2__* bt_bdev; } ;
struct TYPE_4__ {TYPE_1__* bd_disk; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int queue_dma_alignment (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
xfs_buftarg_dma_alignment(struct xfs_buftarg *bt)
{
	return queue_dma_alignment(bt->bt_bdev->bd_disk->queue);
}