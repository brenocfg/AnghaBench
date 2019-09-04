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
typedef  int u16 ;
struct bcm2708_dma_cb {int info; int length; int stride; scalar_t__* pad; void* src; void* dst; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int BCM2708_DMA_BURST (int) ; 
 int BCM2708_DMA_D_INC ; 
 int BCM2708_DMA_D_WIDTH ; 
 int BCM2708_DMA_S_INC ; 
 int BCM2708_DMA_S_WIDTH ; 
 int BCM2708_DMA_TDMODE ; 

__attribute__((used)) static void set_dma_cb(struct bcm2708_dma_cb *cb,
		       int        burst_size,
		       dma_addr_t dst,
		       int        dst_stride,
		       dma_addr_t src,
		       int        src_stride,
		       int        w,
		       int        h)
{
	cb->info = BCM2708_DMA_BURST(burst_size) | BCM2708_DMA_S_WIDTH |
		   BCM2708_DMA_S_INC | BCM2708_DMA_D_WIDTH |
		   BCM2708_DMA_D_INC | BCM2708_DMA_TDMODE;
	cb->dst = dst;
	cb->src = src;
	/*
	 * This is not really obvious from the DMA documentation,
	 * but the top 16 bits must be programmmed to "height -1"
	 * and not "height" in 2D mode.
	 */
	cb->length = ((h - 1) << 16) | w;
	cb->stride = ((dst_stride - w) << 16) | (u16)(src_stride - w);
	cb->pad[0] = 0;
	cb->pad[1] = 0;
}