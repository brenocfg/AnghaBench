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
struct comedi_isadma_desc {unsigned int size; int /*<<< orphan*/  chan; } ;
struct comedi_isadma {size_t cur_dma; struct comedi_isadma_desc* desc; } ;

/* Variables and functions */
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 unsigned int get_dma_residue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_bridge_buggy ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 

unsigned int comedi_isadma_poll(struct comedi_isadma *dma)
{
	struct comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	unsigned long flags;
	unsigned int result;
	unsigned int result1;

	flags = claim_dma_lock();
	clear_dma_ff(desc->chan);
	if (!isa_dma_bridge_buggy)
		disable_dma(desc->chan);
	result = get_dma_residue(desc->chan);
	/*
	 * Read the counter again and choose higher value in order to
	 * avoid reading during counter lower byte roll over if the
	 * isa_dma_bridge_buggy is set.
	 */
	result1 = get_dma_residue(desc->chan);
	if (!isa_dma_bridge_buggy)
		enable_dma(desc->chan);
	release_dma_lock(flags);

	if (result < result1)
		result = result1;
	if (result >= desc->size || result == 0)
		return 0;
	return desc->size - result;
}