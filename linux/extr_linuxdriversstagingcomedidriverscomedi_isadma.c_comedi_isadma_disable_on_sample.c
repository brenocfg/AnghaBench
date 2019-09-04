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
 unsigned int comedi_isadma_disable (unsigned int) ; 
 int /*<<< orphan*/  enable_dma (unsigned int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

unsigned int comedi_isadma_disable_on_sample(unsigned int dma_chan,
					     unsigned int size)
{
	int stalled = 0;
	unsigned long flags;
	unsigned int residue;
	unsigned int new_residue;

	residue = comedi_isadma_disable(dma_chan);
	while (residue % size) {
		/* residue is a partial sample, enable DMA to allow more data */
		flags = claim_dma_lock();
		enable_dma(dma_chan);
		release_dma_lock(flags);

		udelay(2);
		new_residue = comedi_isadma_disable(dma_chan);

		/* is DMA stalled? */
		if (new_residue == residue) {
			stalled++;
			if (stalled > 10)
				break;
		} else {
			residue = new_residue;
			stalled = 0;
		}
	}
	return residue;
}