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
struct us_data {int /*<<< orphan*/  recv_bulk_pipe; int /*<<< orphan*/  send_bulk_pipe; } ;

/* Variables and functions */
 int ALAUDA_BULK_CMD ; 
 int ALAUDA_BULK_GET_STATUS2 ; 
 unsigned char ALAUDA_STATUS_ERROR ; 
 int MEDIA_PORT (struct us_data*) ; 
 int USB_STOR_XFER_ERROR ; 
 int USB_STOR_XFER_GOOD ; 
 int usb_stor_bulk_transfer_buf (struct us_data*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,unsigned char*) ; 

__attribute__((used)) static int alauda_check_status2(struct us_data *us)
{
	int rc;
	unsigned char command[] = {
		ALAUDA_BULK_CMD, ALAUDA_BULK_GET_STATUS2,
		0, 0, 0, 0, 3, 0, MEDIA_PORT(us)
	};
	unsigned char data[3];

	rc = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, NULL);
	if (rc != USB_STOR_XFER_GOOD)
		return rc;

	rc = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
		data, 3, NULL);
	if (rc != USB_STOR_XFER_GOOD)
		return rc;

	usb_stor_dbg(us, "%3ph\n", data);
	if (data[0] & ALAUDA_STATUS_ERROR)
		return USB_STOR_XFER_ERROR;

	return USB_STOR_XFER_GOOD;
}