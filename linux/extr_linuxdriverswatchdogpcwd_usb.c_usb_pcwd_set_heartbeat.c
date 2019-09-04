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
struct usb_pcwd_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WRITE_WATCHDOG_TIMEOUT ; 
 int EINVAL ; 
 int heartbeat ; 
 int /*<<< orphan*/  usb_pcwd_send_command (struct usb_pcwd_private*,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int usb_pcwd_set_heartbeat(struct usb_pcwd_private *usb_pcwd, int t)
{
	unsigned char msb = t / 256;
	unsigned char lsb = t % 256;

	if ((t < 0x0001) || (t > 0xFFFF))
		return -EINVAL;

	/* Write new heartbeat to watchdog */
	usb_pcwd_send_command(usb_pcwd, CMD_WRITE_WATCHDOG_TIMEOUT, &msb, &lsb);

	heartbeat = t;
	return 0;
}