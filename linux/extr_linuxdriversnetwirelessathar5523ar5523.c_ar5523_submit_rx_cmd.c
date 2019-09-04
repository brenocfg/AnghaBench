#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ar5523 {TYPE_1__* rx_cmd_urb; int /*<<< orphan*/  rx_cmd_buf; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_MAX_RXCMDSZ ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  ar5523_cmd_rx_cb ; 
 int /*<<< orphan*/  ar5523_cmd_rx_pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_err (struct ar5523*,char*,int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ar5523*) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5523_submit_rx_cmd(struct ar5523 *ar)
{
	int error;

	usb_fill_bulk_urb(ar->rx_cmd_urb, ar->dev,
			  ar5523_cmd_rx_pipe(ar->dev), ar->rx_cmd_buf,
			  AR5523_MAX_RXCMDSZ, ar5523_cmd_rx_cb, ar);
	ar->rx_cmd_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = usb_submit_urb(ar->rx_cmd_urb, GFP_ATOMIC);
	if (error) {
		if (error != -ENODEV)
			ar5523_err(ar, "error %d when submitting rx urb\n",
				   error);
		return error;
	}
	return 0;
}