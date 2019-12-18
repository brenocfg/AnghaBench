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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ SWIOTLB_FORCE ; 
 scalar_t__ dma_capable (struct device*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ swiotlb_force ; 

__attribute__((used)) static inline bool dma_direct_possible(struct device *dev, dma_addr_t dma_addr,
		size_t size)
{
	return swiotlb_force != SWIOTLB_FORCE &&
		dma_capable(dev, dma_addr, size);
}