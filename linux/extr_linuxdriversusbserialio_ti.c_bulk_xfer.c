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
struct usb_serial {TYPE_1__** port; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bulk_out_endpointAddress; } ;

/* Variables and functions */
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bulk_xfer(struct usb_serial *serial, void *buffer,
						int length, int *num_sent)
{
	int status;

	status = usb_bulk_msg(serial->dev,
			usb_sndbulkpipe(serial->dev,
				serial->port[0]->bulk_out_endpointAddress),
			buffer, length, num_sent, 1000);
	return status;
}