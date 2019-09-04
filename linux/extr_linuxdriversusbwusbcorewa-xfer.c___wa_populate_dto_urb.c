#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wa_xfer {TYPE_1__* urb; scalar_t__ is_dma; } ;
struct wa_seg {TYPE_2__* dto_urb; } ;
struct TYPE_4__ {size_t transfer_buffer_length; int /*<<< orphan*/ * sg; scalar_t__ num_sgs; int /*<<< orphan*/ * transfer_buffer; scalar_t__ num_mapped_sgs; int /*<<< orphan*/  transfer_flags; scalar_t__ transfer_dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  sg; int /*<<< orphan*/ * transfer_buffer; scalar_t__ transfer_dma; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/ * wa_xfer_create_subset_sg (int /*<<< orphan*/ ,size_t,size_t,scalar_t__*) ; 

__attribute__((used)) static int __wa_populate_dto_urb(struct wa_xfer *xfer,
	struct wa_seg *seg, size_t buf_itr_offset, size_t buf_itr_size)
{
	int result = 0;

	if (xfer->is_dma) {
		seg->dto_urb->transfer_dma =
			xfer->urb->transfer_dma + buf_itr_offset;
		seg->dto_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		seg->dto_urb->sg = NULL;
		seg->dto_urb->num_sgs = 0;
	} else {
		/* do buffer or SG processing. */
		seg->dto_urb->transfer_flags &=
			~URB_NO_TRANSFER_DMA_MAP;
		/* this should always be 0 before a resubmit. */
		seg->dto_urb->num_mapped_sgs = 0;

		if (xfer->urb->transfer_buffer) {
			seg->dto_urb->transfer_buffer =
				xfer->urb->transfer_buffer +
				buf_itr_offset;
			seg->dto_urb->sg = NULL;
			seg->dto_urb->num_sgs = 0;
		} else {
			seg->dto_urb->transfer_buffer = NULL;

			/*
			 * allocate an SG list to store seg_size bytes
			 * and copy the subset of the xfer->urb->sg that
			 * matches the buffer subset we are about to
			 * read.
			 */
			seg->dto_urb->sg = wa_xfer_create_subset_sg(
				xfer->urb->sg,
				buf_itr_offset, buf_itr_size,
				&(seg->dto_urb->num_sgs));
			if (!(seg->dto_urb->sg))
				result = -ENOMEM;
		}
	}
	seg->dto_urb->transfer_buffer_length = buf_itr_size;

	return result;
}