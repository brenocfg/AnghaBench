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
typedef  int /*<<< orphan*/  u32 ;
struct sprd_mcdt_chan {int dummy; } ;
typedef  enum sprd_mcdt_dma_chan { ____Placeholder_sprd_mcdt_dma_chan } sprd_mcdt_dma_chan ;

/* Variables and functions */
 int EINVAL ; 

int sprd_mcdt_chan_dma_enable(struct sprd_mcdt_chan *chan,
			      enum sprd_mcdt_dma_chan dma_chan, u32 water_mark)
{
	return -EINVAL;
}