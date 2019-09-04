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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCT_U232_MAX_SIZE ; 
 unsigned char MCT_U232_MCR_DTR ; 
 unsigned char MCT_U232_MCR_NONE ; 
 unsigned char MCT_U232_MCR_RTS ; 
 int /*<<< orphan*/  MCT_U232_SET_MODEM_CTRL_REQUEST ; 
 int /*<<< orphan*/  MCT_U232_SET_MODEM_CTRL_SIZE ; 
 int /*<<< orphan*/  MCT_U232_SET_REQUEST_TYPE ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  WDR_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mct_u232_set_modem_ctrl(struct usb_serial_port *port,
				   unsigned int control_state)
{
	int rc;
	unsigned char mcr;
	unsigned char *buf;

	buf = kmalloc(MCT_U232_MAX_SIZE, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	mcr = MCT_U232_MCR_NONE;
	if (control_state & TIOCM_DTR)
		mcr |= MCT_U232_MCR_DTR;
	if (control_state & TIOCM_RTS)
		mcr |= MCT_U232_MCR_RTS;

	buf[0] = mcr;
	rc = usb_control_msg(port->serial->dev, usb_sndctrlpipe(port->serial->dev, 0),
			MCT_U232_SET_MODEM_CTRL_REQUEST,
			MCT_U232_SET_REQUEST_TYPE,
			0, 0, buf, MCT_U232_SET_MODEM_CTRL_SIZE,
			WDR_TIMEOUT);
	kfree(buf);

	dev_dbg(&port->dev, "set_modem_ctrl: state=0x%x ==> mcr=0x%x\n", control_state, mcr);

	if (rc < 0) {
		dev_err(&port->dev, "Set MODEM CTRL 0x%x failed (error = %d)\n", mcr, rc);
		return rc;
	}
	return 0;
}