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
struct device {int /*<<< orphan*/  bus_dma_mask; int /*<<< orphan*/  coherent_dma_mask; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 size_t min_not_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t phys_to_dma_direct (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dma_coherent_ok(struct device *dev, phys_addr_t phys, size_t size)
{
	return phys_to_dma_direct(dev, phys) + size - 1 <=
			min_not_zero(dev->coherent_dma_mask, dev->bus_dma_mask);
}