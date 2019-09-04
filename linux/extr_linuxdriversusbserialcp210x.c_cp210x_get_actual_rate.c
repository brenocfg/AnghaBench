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
struct usb_serial {int dummy; } ;
struct cp210x_serial_private {int /*<<< orphan*/  max_speed; } ;
typedef  int speed_t ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (int,int) ; 
 int clamp (int,unsigned int,int /*<<< orphan*/ ) ; 
 struct cp210x_serial_private* usb_get_serial_data (struct usb_serial*) ; 

__attribute__((used)) static speed_t cp210x_get_actual_rate(struct usb_serial *serial, speed_t baud)
{
	struct cp210x_serial_private *priv = usb_get_serial_data(serial);
	unsigned int prescale = 1;
	unsigned int div;

	baud = clamp(baud, 300u, priv->max_speed);

	if (baud <= 365)
		prescale = 4;

	div = DIV_ROUND_CLOSEST(48000000, 2 * prescale * baud);
	baud = 48000000 / (2 * prescale * div);

	return baud;
}