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
 int /*<<< orphan*/  dma_map_single (struct device*,void*,size_t,int) ; 

__attribute__((used)) static u64 niu_pci_map_single(struct device *dev, void *cpu_addr,
			      size_t size,
			      enum dma_data_direction direction)
{
	return dma_map_single(dev, cpu_addr, size, direction);
}