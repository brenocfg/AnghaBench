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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
#define  DMA_BIDIRECTIONAL 131 
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 

__attribute__((used)) static const char *data_dir_name(enum dma_data_direction d)
{
	switch (d) {
	case DMA_BIDIRECTIONAL:	return "BIDI";
	case DMA_TO_DEVICE:	return "WRITE";
	case DMA_FROM_DEVICE:	return "READ";
	case DMA_NONE:		return "NONE";
	}

	return "(?)";
}