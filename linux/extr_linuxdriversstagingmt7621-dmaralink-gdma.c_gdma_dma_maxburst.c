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
typedef  int u32 ;
typedef  enum gdma_dma_transfer_size { ____Placeholder_gdma_dma_transfer_size } gdma_dma_transfer_size ;

/* Variables and functions */
 int GDMA_TRANSFER_SIZE_16BYTE ; 
 int GDMA_TRANSFER_SIZE_32BYTE ; 
 int GDMA_TRANSFER_SIZE_4BYTE ; 
 int GDMA_TRANSFER_SIZE_64BYTE ; 
 int GDMA_TRANSFER_SIZE_8BYTE ; 

__attribute__((used)) static enum gdma_dma_transfer_size gdma_dma_maxburst(u32 maxburst)
{
	if (maxburst < 2)
		return GDMA_TRANSFER_SIZE_4BYTE;
	else if (maxburst < 4)
		return GDMA_TRANSFER_SIZE_8BYTE;
	else if (maxburst < 8)
		return GDMA_TRANSFER_SIZE_16BYTE;
	else if (maxburst < 16)
		return GDMA_TRANSFER_SIZE_32BYTE;
	else
		return GDMA_TRANSFER_SIZE_64BYTE;
}