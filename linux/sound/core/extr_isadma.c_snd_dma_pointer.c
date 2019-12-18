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

/* Variables and functions */
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (unsigned long) ; 
 int /*<<< orphan*/  disable_dma (unsigned long) ; 
 int /*<<< orphan*/  enable_dma (unsigned long) ; 
 unsigned int get_dma_residue (unsigned long) ; 
 int /*<<< orphan*/  isa_dma_bridge_buggy ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

unsigned int snd_dma_pointer(unsigned long dma, unsigned int size)
{
	unsigned long flags;
	unsigned int result, result1;

	flags = claim_dma_lock();
	clear_dma_ff(dma);
	if (!isa_dma_bridge_buggy)
		disable_dma(dma);
	result = get_dma_residue(dma);
	/*
	 * HACK - read the counter again and choose higher value in order to
	 * avoid reading during counter lower byte roll over if the
	 * isa_dma_bridge_buggy is set.
	 */
	result1 = get_dma_residue(dma);
	if (!isa_dma_bridge_buggy)
		enable_dma(dma);
	release_dma_lock(flags);
	if (unlikely(result < result1))
		result = result1;
#ifdef CONFIG_SND_DEBUG
	if (result > size)
		pr_err("ALSA: pointer (0x%x) for DMA #%ld is greater than transfer size (0x%x)\n", result, dma, size);
#endif
	if (result >= size || result == 0)
		return 0;
	else
		return size - result;
}