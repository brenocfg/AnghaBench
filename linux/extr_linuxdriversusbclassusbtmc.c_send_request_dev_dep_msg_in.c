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
typedef  int u8 ;
struct usbtmc_file_data {int term_char_enabled; int term_char; int /*<<< orphan*/  timeout; struct usbtmc_device_data* data; } ;
struct usbtmc_device_data {int bTag; int bTag_last_write; TYPE_1__* intf; int /*<<< orphan*/  bulk_out; int /*<<< orphan*/  usb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USBTMC_HEADER_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_request_dev_dep_msg_in(struct usbtmc_file_data *file_data,
				       size_t transfer_size)
{
	struct usbtmc_device_data *data = file_data->data;
	int retval;
	u8 *buffer;
	int actual;

	buffer = kmalloc(USBTMC_HEADER_SIZE, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;
	/* Setup IO buffer for REQUEST_DEV_DEP_MSG_IN message
	 * Refer to class specs for details
	 */
	buffer[0] = 2;
	buffer[1] = data->bTag;
	buffer[2] = ~data->bTag;
	buffer[3] = 0; /* Reserved */
	buffer[4] = transfer_size >> 0;
	buffer[5] = transfer_size >> 8;
	buffer[6] = transfer_size >> 16;
	buffer[7] = transfer_size >> 24;
	buffer[8] = file_data->term_char_enabled * 2;
	/* Use term character? */
	buffer[9] = file_data->term_char;
	buffer[10] = 0; /* Reserved */
	buffer[11] = 0; /* Reserved */

	/* Send bulk URB */
	retval = usb_bulk_msg(data->usb_dev,
			      usb_sndbulkpipe(data->usb_dev,
					      data->bulk_out),
			      buffer, USBTMC_HEADER_SIZE,
			      &actual, file_data->timeout);

	/* Store bTag (in case we need to abort) */
	data->bTag_last_write = data->bTag;

	/* Increment bTag -- and increment again if zero */
	data->bTag++;
	if (!data->bTag)
		data->bTag++;

	kfree(buffer);
	if (retval < 0) {
		dev_err(&data->intf->dev, "usb_bulk_msg in send_request_dev_dep_msg_in() returned %d\n", retval);
		return retval;
	}

	return 0;
}