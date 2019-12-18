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
struct au1xpsc_audio_dmadata {int msbits; void* ddma_chan; int /*<<< orphan*/  ddma_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR_CMD0_ALWAYS ; 
 int ENOMEM ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  au1x_pcm_dbdma_free (struct au1xpsc_audio_dmadata*) ; 
 int /*<<< orphan*/  au1x_pcm_dmarx_cb ; 
 int /*<<< orphan*/  au1x_pcm_dmatx_cb ; 
 void* au1xxx_dbdma_chan_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  au1xxx_dbdma_reset (void*) ; 
 int /*<<< orphan*/  au1xxx_dbdma_ring_alloc (void*,int) ; 
 int /*<<< orphan*/  au1xxx_dbdma_set_devwidth (void*,int) ; 
 int /*<<< orphan*/  au1xxx_dbdma_stop (void*) ; 

__attribute__((used)) static int au1x_pcm_dbdma_realloc(struct au1xpsc_audio_dmadata *pcd,
				 int stype, int msbits)
{
	/* DMA only in 8/16/32 bit widths */
	if (msbits == 24)
		msbits = 32;

	/* check current config: correct bits and descriptors allocated? */
	if ((pcd->ddma_chan) && (msbits == pcd->msbits))
		goto out;	/* all ok! */

	au1x_pcm_dbdma_free(pcd);

	if (stype == SNDRV_PCM_STREAM_CAPTURE)
		pcd->ddma_chan = au1xxx_dbdma_chan_alloc(pcd->ddma_id,
					DSCR_CMD0_ALWAYS,
					au1x_pcm_dmarx_cb, (void *)pcd);
	else
		pcd->ddma_chan = au1xxx_dbdma_chan_alloc(DSCR_CMD0_ALWAYS,
					pcd->ddma_id,
					au1x_pcm_dmatx_cb, (void *)pcd);

	if (!pcd->ddma_chan)
		return -ENOMEM;

	au1xxx_dbdma_set_devwidth(pcd->ddma_chan, msbits);
	au1xxx_dbdma_ring_alloc(pcd->ddma_chan, 2);

	pcd->msbits = msbits;

	au1xxx_dbdma_stop(pcd->ddma_chan);
	au1xxx_dbdma_reset(pcd->ddma_chan);

out:
	return 0;
}