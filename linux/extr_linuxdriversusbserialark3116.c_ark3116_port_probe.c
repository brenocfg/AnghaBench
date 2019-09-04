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
struct usb_serial_port {int /*<<< orphan*/  dev; struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct ark3116_private {int quot; int lcr; scalar_t__ irda; scalar_t__ mcr; scalar_t__ hcr; int /*<<< orphan*/  status_lock; int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UART_DLL ; 
 int UART_DLM ; 
 int UART_FCR ; 
 int UART_IER ; 
 int UART_LCR ; 
 int UART_LCR_DLAB ; 
 int UART_LCR_WLEN8 ; 
 int UART_MCR ; 
 int /*<<< orphan*/  ark3116_write_reg (struct usb_serial*,int,int) ; 
 int calc_divisor (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ is_irda (struct usb_serial*) ; 
 struct ark3116_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct ark3116_private*) ; 

__attribute__((used)) static int ark3116_port_probe(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;
	struct ark3116_private *priv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->hw_lock);
	spin_lock_init(&priv->status_lock);

	priv->irda = is_irda(serial);

	usb_set_serial_port_data(port, priv);

	/* setup the hardware */
	ark3116_write_reg(serial, UART_IER, 0);
	/* disable DMA */
	ark3116_write_reg(serial, UART_FCR, 0);
	/* handshake control */
	priv->hcr = 0;
	ark3116_write_reg(serial, 0x8     , 0);
	/* modem control */
	priv->mcr = 0;
	ark3116_write_reg(serial, UART_MCR, 0);

	if (!(priv->irda)) {
		ark3116_write_reg(serial, 0xb , 0);
	} else {
		ark3116_write_reg(serial, 0xb , 1);
		ark3116_write_reg(serial, 0xc , 0);
		ark3116_write_reg(serial, 0xd , 0x41);
		ark3116_write_reg(serial, 0xa , 1);
	}

	/* setup baudrate */
	ark3116_write_reg(serial, UART_LCR, UART_LCR_DLAB);

	/* setup for 9600 8N1 */
	priv->quot = calc_divisor(9600);
	ark3116_write_reg(serial, UART_DLL, priv->quot & 0xff);
	ark3116_write_reg(serial, UART_DLM, (priv->quot>>8) & 0xff);

	priv->lcr = UART_LCR_WLEN8;
	ark3116_write_reg(serial, UART_LCR, UART_LCR_WLEN8);

	ark3116_write_reg(serial, 0xe, 0);

	if (priv->irda)
		ark3116_write_reg(serial, 0x9, 0);

	dev_info(&port->dev, "using %s mode\n", priv->irda ? "IrDA" : "RS232");

	return 0;
}