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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
#define  DMA_BIDIRECTIONAL 131 
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  UIS_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  UIS_DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  UIS_DMA_NONE ; 
 int /*<<< orphan*/  UIS_DMA_TO_DEVICE ; 

__attribute__((used)) static u32 dma_data_dir_linux_to_spar(enum dma_data_direction d)
{
	switch (d) {
	case DMA_BIDIRECTIONAL:
		return UIS_DMA_BIDIRECTIONAL;
	case DMA_TO_DEVICE:
		return UIS_DMA_TO_DEVICE;
	case DMA_FROM_DEVICE:
		return UIS_DMA_FROM_DEVICE;
	case DMA_NONE:
		return UIS_DMA_NONE;
	default:
		return UIS_DMA_NONE;
	}
}