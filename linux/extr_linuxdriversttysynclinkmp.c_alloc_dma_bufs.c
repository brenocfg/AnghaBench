#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int port_num; int max_frame_size; unsigned short tx_buf_count; unsigned short rx_buf_count; int /*<<< orphan*/  device_name; int /*<<< orphan*/  tx_buf_list_ex; int /*<<< orphan*/  tx_buf_list; int /*<<< orphan*/  rx_buf_list_ex; int /*<<< orphan*/  rx_buf_list; TYPE_1__** port_array; } ;
struct TYPE_8__ {int last_mem_alloc; } ;
typedef  TYPE_2__ SLMP_INFO ;
typedef  int /*<<< orphan*/  SCADESC ;

/* Variables and functions */
 int BUFFERLISTSIZE ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int ENOMEM ; 
 int SCABUFSIZE ; 
 void* SCAMAXDESC ; 
 int SCA_MEM_SIZE ; 
 scalar_t__ alloc_buf_list (TYPE_2__*) ; 
 scalar_t__ alloc_frame_bufs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ alloc_tmp_rx_buf (TYPE_2__*) ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rx_reset_buffers (TYPE_2__*) ; 

__attribute__((used)) static int alloc_dma_bufs(SLMP_INFO *info)
{
	unsigned short BuffersPerFrame;
	unsigned short BufferCount;

	// Force allocation to start at 64K boundary for each port.
	// This is necessary because *all* buffer descriptors for a port
	// *must* be in the same 64K block. All descriptors on a port
	// share a common 'base' address (upper 8 bits of 24 bits) programmed
	// into the CBP register.
	info->port_array[0]->last_mem_alloc = (SCA_MEM_SIZE/4) * info->port_num;

	/* Calculate the number of DMA buffers necessary to hold the */
	/* largest allowable frame size. Note: If the max frame size is */
	/* not an even multiple of the DMA buffer size then we need to */
	/* round the buffer count per frame up one. */

	BuffersPerFrame = (unsigned short)(info->max_frame_size/SCABUFSIZE);
	if ( info->max_frame_size % SCABUFSIZE )
		BuffersPerFrame++;

	/* calculate total number of data buffers (SCABUFSIZE) possible
	 * in one ports memory (SCA_MEM_SIZE/4) after allocating memory
	 * for the descriptor list (BUFFERLISTSIZE).
	 */
	BufferCount = (SCA_MEM_SIZE/4 - BUFFERLISTSIZE)/SCABUFSIZE;

	/* limit number of buffers to maximum amount of descriptors */
	if (BufferCount > BUFFERLISTSIZE/sizeof(SCADESC))
		BufferCount = BUFFERLISTSIZE/sizeof(SCADESC);

	/* use enough buffers to transmit one max size frame */
	info->tx_buf_count = BuffersPerFrame + 1;

	/* never use more than half the available buffers for transmit */
	if (info->tx_buf_count > (BufferCount/2))
		info->tx_buf_count = BufferCount/2;

	if (info->tx_buf_count > SCAMAXDESC)
		info->tx_buf_count = SCAMAXDESC;

	/* use remaining buffers for receive */
	info->rx_buf_count = BufferCount - info->tx_buf_count;

	if (info->rx_buf_count > SCAMAXDESC)
		info->rx_buf_count = SCAMAXDESC;

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk("%s(%d):%s Allocating %d TX and %d RX DMA buffers.\n",
			__FILE__,__LINE__, info->device_name,
			info->tx_buf_count,info->rx_buf_count);

	if ( alloc_buf_list( info ) < 0 ||
		alloc_frame_bufs(info,
		  			info->rx_buf_list,
		  			info->rx_buf_list_ex,
					info->rx_buf_count) < 0 ||
		alloc_frame_bufs(info,
					info->tx_buf_list,
					info->tx_buf_list_ex,
					info->tx_buf_count) < 0 ||
		alloc_tmp_rx_buf(info) < 0 ) {
		printk("%s(%d):%s Can't allocate DMA buffer memory\n",
			__FILE__,__LINE__, info->device_name);
		return -ENOMEM;
	}

	rx_reset_buffers( info );

	return 0;
}