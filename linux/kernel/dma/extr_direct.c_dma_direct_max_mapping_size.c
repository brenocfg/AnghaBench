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

/* Variables and functions */
 size_t SIZE_MAX ; 
 scalar_t__ SWIOTLB_FORCE ; 
 scalar_t__ dma_addressing_limited (struct device*) ; 
 scalar_t__ is_swiotlb_active () ; 
 scalar_t__ swiotlb_force ; 
 size_t swiotlb_max_mapping_size (struct device*) ; 

size_t dma_direct_max_mapping_size(struct device *dev)
{
	/* If SWIOTLB is active, use its maximum mapping size */
	if (is_swiotlb_active() &&
	    (dma_addressing_limited(dev) || swiotlb_force == SWIOTLB_FORCE))
		return swiotlb_max_mapping_size(dev);
	return SIZE_MAX;
}