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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {int /*<<< orphan*/  interrupt_out_endpointAddress; TYPE_1__* serial; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metrousb_is_unidirectional_mode (TYPE_1__*) ; 
 int usb_interrupt_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int metrousb_send_unidirectional_cmd(u8 cmd, struct usb_serial_port *port)
{
	int ret;
	int actual_len;
	u8 *buffer_cmd = NULL;

	if (!metrousb_is_unidirectional_mode(port->serial))
		return 0;

	buffer_cmd = kzalloc(sizeof(cmd), GFP_KERNEL);
	if (!buffer_cmd)
		return -ENOMEM;

	*buffer_cmd = cmd;

	ret = usb_interrupt_msg(port->serial->dev,
		usb_sndintpipe(port->serial->dev, port->interrupt_out_endpointAddress),
		buffer_cmd, sizeof(cmd),
		&actual_len, USB_CTRL_SET_TIMEOUT);

	kfree(buffer_cmd);

	if (ret < 0)
		return ret;
	else if (actual_len != sizeof(cmd))
		return -EIO;
	return 0;
}