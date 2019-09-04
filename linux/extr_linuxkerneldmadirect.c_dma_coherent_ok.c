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
struct device {size_t coherent_dma_mask; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 size_t __phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ force_dma_unencrypted () ; 
 size_t phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dma_coherent_ok(struct device *dev, phys_addr_t phys, size_t size)
{
	dma_addr_t addr = force_dma_unencrypted() ?
		__phys_to_dma(dev, phys) : phys_to_dma(dev, phys);
	return addr + size - 1 <= dev->coherent_dma_mask;
}