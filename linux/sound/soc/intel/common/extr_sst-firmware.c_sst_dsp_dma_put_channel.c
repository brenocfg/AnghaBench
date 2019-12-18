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
struct sst_dsp {struct sst_dma* dma; } ;
struct sst_dma {int /*<<< orphan*/ * ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

void sst_dsp_dma_put_channel(struct sst_dsp *dsp)
{
	struct sst_dma *dma = dsp->dma;

	if (!dma->ch)
		return;

	dma_release_channel(dma->ch);
	dma->ch = NULL;
}