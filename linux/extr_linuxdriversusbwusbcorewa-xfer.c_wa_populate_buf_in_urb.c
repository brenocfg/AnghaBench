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
struct wa_xfer {unsigned int seg_size; TYPE_1__* urb; scalar_t__ is_dma; struct wa_seg** seg; } ;
struct wa_seg {int dummy; } ;
struct urb {unsigned int transfer_buffer_length; struct wa_seg* context; int /*<<< orphan*/ * transfer_buffer; scalar_t__ num_sgs; int /*<<< orphan*/ * sg; int /*<<< orphan*/  transfer_flags; scalar_t__ transfer_dma; scalar_t__ num_mapped_sgs; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/  sg; int /*<<< orphan*/ * transfer_buffer; scalar_t__ transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/ * wa_xfer_create_subset_sg (int /*<<< orphan*/ ,unsigned int,unsigned int,scalar_t__*) ; 

__attribute__((used)) static int wa_populate_buf_in_urb(struct urb *buf_in_urb, struct wa_xfer *xfer,
	unsigned int seg_idx, unsigned int bytes_transferred)
{
	int result = 0;
	struct wa_seg *seg = xfer->seg[seg_idx];

	BUG_ON(buf_in_urb->status == -EINPROGRESS);
	/* this should always be 0 before a resubmit. */
	buf_in_urb->num_mapped_sgs	= 0;

	if (xfer->is_dma) {
		buf_in_urb->transfer_dma = xfer->urb->transfer_dma
			+ (seg_idx * xfer->seg_size);
		buf_in_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		buf_in_urb->transfer_buffer = NULL;
		buf_in_urb->sg = NULL;
		buf_in_urb->num_sgs = 0;
	} else {
		/* do buffer or SG processing. */
		buf_in_urb->transfer_flags &= ~URB_NO_TRANSFER_DMA_MAP;

		if (xfer->urb->transfer_buffer) {
			buf_in_urb->transfer_buffer =
				xfer->urb->transfer_buffer
				+ (seg_idx * xfer->seg_size);
			buf_in_urb->sg = NULL;
			buf_in_urb->num_sgs = 0;
		} else {
			/* allocate an SG list to store seg_size bytes
				and copy the subset of the xfer->urb->sg
				that matches the buffer subset we are
				about to read. */
			buf_in_urb->sg = wa_xfer_create_subset_sg(
				xfer->urb->sg,
				seg_idx * xfer->seg_size,
				bytes_transferred,
				&(buf_in_urb->num_sgs));

			if (!(buf_in_urb->sg)) {
				buf_in_urb->num_sgs	= 0;
				result = -ENOMEM;
			}
			buf_in_urb->transfer_buffer = NULL;
		}
	}
	buf_in_urb->transfer_buffer_length = bytes_transferred;
	buf_in_urb->context = seg;

	return result;
}