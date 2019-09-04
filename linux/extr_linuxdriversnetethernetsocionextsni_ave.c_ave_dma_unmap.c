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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ave_desc {scalar_t__ skbs_dma; int /*<<< orphan*/  skbs_dmalen; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ave_dma_unmap(struct net_device *ndev, struct ave_desc *desc,
			  enum dma_data_direction dir)
{
	if (!desc->skbs_dma)
		return;

	dma_unmap_single(ndev->dev.parent,
			 desc->skbs_dma, desc->skbs_dmalen, dir);
	desc->skbs_dma = 0;
}