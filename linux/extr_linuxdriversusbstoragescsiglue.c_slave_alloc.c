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
struct us_data {scalar_t__ protocol; scalar_t__ max_lun; } ;
struct scsi_device {int inquiry_len; int /*<<< orphan*/  sdev_bflags; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLIST_FORCELUN ; 
 scalar_t__ USB_PR_BULK ; 
 int /*<<< orphan*/  blk_queue_update_dma_alignment (int /*<<< orphan*/ ,int) ; 
 struct us_data* host_to_us (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slave_alloc (struct scsi_device *sdev)
{
	struct us_data *us = host_to_us(sdev->host);

	/*
	 * Set the INQUIRY transfer length to 36.  We don't use any of
	 * the extra data and many devices choke if asked for more or
	 * less than 36 bytes.
	 */
	sdev->inquiry_len = 36;

	/*
	 * USB has unusual DMA-alignment requirements: Although the
	 * starting address of each scatter-gather element doesn't matter,
	 * the length of each element except the last must be divisible
	 * by the Bulk maxpacket value.  There's currently no way to
	 * express this by block-layer constraints, so we'll cop out
	 * and simply require addresses to be aligned at 512-byte
	 * boundaries.  This is okay since most block I/O involves
	 * hardware sectors that are multiples of 512 bytes in length,
	 * and since host controllers up through USB 2.0 have maxpacket
	 * values no larger than 512.
	 *
	 * But it doesn't suffice for Wireless USB, where Bulk maxpacket
	 * values can be as large as 2048.  To make that work properly
	 * will require changes to the block layer.
	 */
	blk_queue_update_dma_alignment(sdev->request_queue, (512 - 1));

	/* Tell the SCSI layer if we know there is more than one LUN */
	if (us->protocol == USB_PR_BULK && us->max_lun > 0)
		sdev->sdev_bflags |= BLIST_FORCELUN;

	return 0;
}