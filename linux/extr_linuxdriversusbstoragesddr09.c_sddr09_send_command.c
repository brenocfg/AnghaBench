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
struct us_data {unsigned int recv_ctrl_pipe; unsigned int send_ctrl_pipe; } ;

/* Variables and functions */
 int EIO ; 
 int EPIPE ; 
 unsigned char USB_DIR_IN ; 
#define  USB_STOR_XFER_GOOD 129 
#define  USB_STOR_XFER_STALLED 128 
 int usb_stor_ctrl_transfer (struct us_data*,unsigned int,unsigned char,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 

__attribute__((used)) static int
sddr09_send_command(struct us_data *us,
		    unsigned char request,
		    unsigned char direction,
		    unsigned char *xfer_data,
		    unsigned int xfer_len) {
	unsigned int pipe;
	unsigned char requesttype = (0x41 | direction);
	int rc;

	// Get the receive or send control pipe number

	if (direction == USB_DIR_IN)
		pipe = us->recv_ctrl_pipe;
	else
		pipe = us->send_ctrl_pipe;

	rc = usb_stor_ctrl_transfer(us, pipe, request, requesttype,
				   0, 0, xfer_data, xfer_len);
	switch (rc) {
		case USB_STOR_XFER_GOOD:	return 0;
		case USB_STOR_XFER_STALLED:	return -EPIPE;
		default:			return -EIO;
	}
}