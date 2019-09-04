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
struct us_data {scalar_t__ iobuf; } ;
struct scsi_cmnd {int dummy; } ;
struct freecom_xfer_wrap {int Type; int /*<<< orphan*/  Pad; int /*<<< orphan*/  Count; scalar_t__ Timeout; } ;

/* Variables and functions */
 int FCM_PACKET_INPUT ; 
 int /*<<< orphan*/  FCM_PACKET_LENGTH ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int USB_STOR_XFER_SHORT ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_stor_bulk_srb (struct us_data*,unsigned int,struct scsi_cmnd*) ; 
 int usb_stor_bulk_transfer_buf (struct us_data*,unsigned int,struct freecom_xfer_wrap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

__attribute__((used)) static int
freecom_readdata (struct scsi_cmnd *srb, struct us_data *us,
		unsigned int ipipe, unsigned int opipe, int count)
{
	struct freecom_xfer_wrap *fxfr =
		(struct freecom_xfer_wrap *) us->iobuf;
	int result;

	fxfr->Type = FCM_PACKET_INPUT | 0x00;
	fxfr->Timeout = 0;    /* Short timeout for debugging. */
	fxfr->Count = cpu_to_le32 (count);
	memset (fxfr->Pad, 0, sizeof (fxfr->Pad));

	usb_stor_dbg(us, "Read data Freecom! (c=%d)\n", count);

	/* Issue the transfer command. */
	result = usb_stor_bulk_transfer_buf (us, opipe, fxfr,
			FCM_PACKET_LENGTH, NULL);
	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Freecom readdata transport error\n");
		return USB_STOR_TRANSPORT_ERROR;
	}

	/* Now transfer all of our blocks. */
	usb_stor_dbg(us, "Start of read\n");
	result = usb_stor_bulk_srb(us, ipipe, srb);
	usb_stor_dbg(us, "freecom_readdata done!\n");

	if (result > USB_STOR_XFER_SHORT)
		return USB_STOR_TRANSPORT_ERROR;
	return USB_STOR_TRANSPORT_GOOD;
}