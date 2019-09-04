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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {int dummy; } ;

/* Variables and functions */
 int cp210x_read_reg_block (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cp210x_read_u8_reg(struct usb_serial_port *port, u8 req, u8 *val)
{
	return cp210x_read_reg_block(port, req, val, sizeof(*val));
}