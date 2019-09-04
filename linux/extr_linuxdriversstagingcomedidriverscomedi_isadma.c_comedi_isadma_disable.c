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
 int /*<<< orphan*/  disable_dma (unsigned int) ; 
 unsigned int get_dma_residue (unsigned int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 

unsigned int comedi_isadma_disable(unsigned int dma_chan)
{
	unsigned long flags;
	unsigned int residue;

	flags = claim_dma_lock();
	disable_dma(dma_chan);
	residue = get_dma_residue(dma_chan);
	release_dma_lock(flags);

	return residue;
}