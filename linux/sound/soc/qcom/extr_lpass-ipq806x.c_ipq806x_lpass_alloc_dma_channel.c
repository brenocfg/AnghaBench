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
struct lpass_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IPQ806X_LPAIF_RDMA_CHAN_MI2S ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 

__attribute__((used)) static int ipq806x_lpass_alloc_dma_channel(struct lpass_data *drvdata, int dir)
{
	if (dir == SNDRV_PCM_STREAM_PLAYBACK)
		return IPQ806X_LPAIF_RDMA_CHAN_MI2S;
	else	/* Capture currently not implemented */
		return -EINVAL;
}