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
struct au1xpsc_audio_dmadata {scalar_t__ msbits; scalar_t__ ddma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  au1xxx_dbdma_chan_free (scalar_t__) ; 
 int /*<<< orphan*/  au1xxx_dbdma_reset (scalar_t__) ; 
 int /*<<< orphan*/  au1xxx_dbdma_stop (scalar_t__) ; 

__attribute__((used)) static void au1x_pcm_dbdma_free(struct au1xpsc_audio_dmadata *pcd)
{
	if (pcd->ddma_chan) {
		au1xxx_dbdma_stop(pcd->ddma_chan);
		au1xxx_dbdma_reset(pcd->ddma_chan);
		au1xxx_dbdma_chan_free(pcd->ddma_chan);
		pcd->ddma_chan = 0;
		pcd->msbits = 0;
	}
}