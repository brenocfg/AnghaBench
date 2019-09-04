#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mgsl_struct {unsigned int rx_buffer_count; unsigned int current_rx_buffer; TYPE_1__* rx_buffer_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ DMABUFFERENTRY ;

/* Variables and functions */
 unsigned long DMABUFFERSIZE ; 

__attribute__((used)) static void mgsl_free_rx_frame_buffers( struct mgsl_struct *info, unsigned int StartIndex, unsigned int EndIndex )
{
	bool Done = false;
	DMABUFFERENTRY *pBufEntry;
	unsigned int Index;

	/* Starting with 1st buffer entry of the frame clear the status */
	/* field and set the count field to DMA Buffer Size. */

	Index = StartIndex;

	while( !Done ) {
		pBufEntry = &(info->rx_buffer_list[Index]);

		if ( Index == EndIndex ) {
			/* This is the last buffer of the frame! */
			Done = true;
		}

		/* reset current buffer for reuse */
//		pBufEntry->status = 0;
//		pBufEntry->count = DMABUFFERSIZE;
		*((unsigned long *)&(pBufEntry->count)) = DMABUFFERSIZE;

		/* advance to next buffer entry in linked list */
		Index++;
		if ( Index == info->rx_buffer_count )
			Index = 0;
	}

	/* set current buffer to next buffer after last buffer of frame */
	info->current_rx_buffer = Index;

}