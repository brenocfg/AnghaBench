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
struct cpdma_ctlr {scalar_t__ state; int /*<<< orphan*/ * channels; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ CPDMA_STATE_IDLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpdma_chan_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpdma_ctlr_stop (struct cpdma_ctlr*) ; 
 int /*<<< orphan*/  cpdma_desc_pool_destroy (struct cpdma_ctlr*) ; 

int cpdma_ctlr_destroy(struct cpdma_ctlr *ctlr)
{
	int ret = 0, i;

	if (!ctlr)
		return -EINVAL;

	if (ctlr->state != CPDMA_STATE_IDLE)
		cpdma_ctlr_stop(ctlr);

	for (i = 0; i < ARRAY_SIZE(ctlr->channels); i++)
		cpdma_chan_destroy(ctlr->channels[i]);

	cpdma_desc_pool_destroy(ctlr);
	return ret;
}