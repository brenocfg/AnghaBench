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
struct usb_serial_port {int /*<<< orphan*/  dev; TYPE_1__* serial; } ;
struct klsi_105_port_settings {int /*<<< orphan*/  unknown2; int /*<<< orphan*/  unknown1; int /*<<< orphan*/  databits; int /*<<< orphan*/  baudrate; int /*<<< orphan*/  pktlen; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KL5KUSB105A_SIO_SET_DATA ; 
 int /*<<< orphan*/  KLSI_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct klsi_105_port_settings*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int klsi_105_chg_port_settings(struct usb_serial_port *port,
				      struct klsi_105_port_settings *settings)
{
	int rc;

	rc = usb_control_msg(port->serial->dev,
			usb_sndctrlpipe(port->serial->dev, 0),
			KL5KUSB105A_SIO_SET_DATA,
			USB_TYPE_VENDOR | USB_DIR_OUT | USB_RECIP_INTERFACE,
			0, /* value */
			0, /* index */
			settings,
			sizeof(struct klsi_105_port_settings),
			KLSI_TIMEOUT);
	if (rc < 0)
		dev_err(&port->dev,
			"Change port settings failed (error = %d)\n", rc);

	dev_dbg(&port->dev,
		"pktlen %u, baudrate 0x%02x, databits %u, u1 %u, u2 %u\n",
		settings->pktlen, settings->baudrate, settings->databits,
		settings->unknown1, settings->unknown2);

	return rc;
}