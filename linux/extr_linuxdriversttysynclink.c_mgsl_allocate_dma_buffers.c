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
struct mgsl_struct {int max_frame_size; scalar_t__ bus_type; unsigned short tx_buffer_count; unsigned short num_tx_dma_buffers; int rx_buffer_count; int /*<<< orphan*/  tx_buffer_list; int /*<<< orphan*/  rx_buffer_list; scalar_t__ last_mem_alloc; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int DMABUFFERSIZE ; 
 int ENOMEM ; 
 unsigned short MAXRXFRAMES ; 
 scalar_t__ MGSL_BUS_TYPE_PCI ; 
 scalar_t__ debug_level ; 
 scalar_t__ mgsl_alloc_buffer_list_memory (struct mgsl_struct*) ; 
 scalar_t__ mgsl_alloc_frame_memory (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mgsl_alloc_intermediate_rxbuffer_memory (struct mgsl_struct*) ; 
 scalar_t__ mgsl_alloc_intermediate_txbuffer_memory (struct mgsl_struct*) ; 
 int /*<<< orphan*/  mgsl_reset_rx_dma_buffers (struct mgsl_struct*) ; 
 int /*<<< orphan*/  mgsl_reset_tx_dma_buffers (struct mgsl_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,...) ; 

__attribute__((used)) static int mgsl_allocate_dma_buffers(struct mgsl_struct *info)
{
	unsigned short BuffersPerFrame;

	info->last_mem_alloc = 0;

	/* Calculate the number of DMA buffers necessary to hold the */
	/* largest allowable frame size. Note: If the max frame size is */
	/* not an even multiple of the DMA buffer size then we need to */
	/* round the buffer count per frame up one. */

	BuffersPerFrame = (unsigned short)(info->max_frame_size/DMABUFFERSIZE);
	if ( info->max_frame_size % DMABUFFERSIZE )
		BuffersPerFrame++;

	if ( info->bus_type == MGSL_BUS_TYPE_PCI ) {
		/*
		 * The PCI adapter has 256KBytes of shared memory to use.
		 * This is 64 PAGE_SIZE buffers.
		 *
		 * The first page is used for padding at this time so the
		 * buffer list does not begin at offset 0 of the PCI
		 * adapter's shared memory.
		 *
		 * The 2nd page is used for the buffer list. A 4K buffer
		 * list can hold 128 DMA_BUFFER structures at 32 bytes
		 * each.
		 *
		 * This leaves 62 4K pages.
		 *
		 * The next N pages are used for transmit frame(s). We
		 * reserve enough 4K page blocks to hold the required
		 * number of transmit dma buffers (num_tx_dma_buffers),
		 * each of MaxFrameSize size.
		 *
		 * Of the remaining pages (62-N), determine how many can
		 * be used to receive full MaxFrameSize inbound frames
		 */
		info->tx_buffer_count = info->num_tx_dma_buffers * BuffersPerFrame;
		info->rx_buffer_count = 62 - info->tx_buffer_count;
	} else {
		/* Calculate the number of PAGE_SIZE buffers needed for */
		/* receive and transmit DMA buffers. */


		/* Calculate the number of DMA buffers necessary to */
		/* hold 7 max size receive frames and one max size transmit frame. */
		/* The receive buffer count is bumped by one so we avoid an */
		/* End of List condition if all receive buffers are used when */
		/* using linked list DMA buffers. */

		info->tx_buffer_count = info->num_tx_dma_buffers * BuffersPerFrame;
		info->rx_buffer_count = (BuffersPerFrame * MAXRXFRAMES) + 6;
		
		/* 
		 * limit total TxBuffers & RxBuffers to 62 4K total 
		 * (ala PCI Allocation) 
		 */
		
		if ( (info->tx_buffer_count + info->rx_buffer_count) > 62 )
			info->rx_buffer_count = 62 - info->tx_buffer_count;

	}

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk("%s(%d):Allocating %d TX and %d RX DMA buffers.\n",
			__FILE__,__LINE__, info->tx_buffer_count,info->rx_buffer_count);
	
	if ( mgsl_alloc_buffer_list_memory( info ) < 0 ||
		  mgsl_alloc_frame_memory(info, info->rx_buffer_list, info->rx_buffer_count) < 0 || 
		  mgsl_alloc_frame_memory(info, info->tx_buffer_list, info->tx_buffer_count) < 0 || 
		  mgsl_alloc_intermediate_rxbuffer_memory(info) < 0  ||
		  mgsl_alloc_intermediate_txbuffer_memory(info) < 0 ) {
		printk("%s(%d):Can't allocate DMA buffer memory\n",__FILE__,__LINE__);
		return -ENOMEM;
	}
	
	mgsl_reset_rx_dma_buffers( info );
  	mgsl_reset_tx_dma_buffers( info );

	return 0;

}