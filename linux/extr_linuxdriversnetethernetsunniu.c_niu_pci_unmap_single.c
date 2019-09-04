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
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void niu_pci_unmap_single(struct device *dev, u64 dma_address,
				 size_t size,
				 enum dma_data_direction direction)
{
	dma_unmap_single(dev, dma_address, size, direction);
}