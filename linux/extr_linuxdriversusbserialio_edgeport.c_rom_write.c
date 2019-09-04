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
struct usb_serial {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_REQUEST_ION_WRITE_ROM ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/  const*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,unsigned char*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rom_write(struct usb_serial *serial, __u16 extAddr, __u16 addr,
					__u16 length, const __u8 *data)
{
	int result;
	__u16 current_length;
	unsigned char *transfer_buffer;

	transfer_buffer =  kmalloc(64, GFP_KERNEL);
	if (!transfer_buffer)
		return -ENOMEM;

	/* need to split these writes up into 64 byte chunks */
	result = 0;
	while (length > 0) {
		if (length > 64)
			current_length = 64;
		else
			current_length = length;
		memcpy(transfer_buffer, data, current_length);
		result = usb_control_msg(serial->dev,
					usb_sndctrlpipe(serial->dev, 0),
					USB_REQUEST_ION_WRITE_ROM, 0x40,
					addr, extAddr,
					transfer_buffer, current_length, 300);
		if (result < 0)
			break;
		length -= current_length;
		addr += current_length;
		data += current_length;
	}

	kfree(transfer_buffer);
	return result;
}