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
struct tty_struct {struct hso_serial* driver_data; } ;
struct hso_serial {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTLCMD ; 
#define  TIOCMIWAIT 128 
 int /*<<< orphan*/  hso_dbg (int,char*,unsigned int,unsigned long) ; 
 int hso_wait_modem_status (struct hso_serial*,unsigned long) ; 

__attribute__((used)) static int hso_serial_ioctl(struct tty_struct *tty,
			    unsigned int cmd, unsigned long arg)
{
	struct hso_serial *serial = tty->driver_data;
	int ret = 0;
	hso_dbg(0x8, "IOCTL cmd: %d, arg: %ld\n", cmd, arg);

	if (!serial)
		return -ENODEV;
	switch (cmd) {
	case TIOCMIWAIT:
		ret = hso_wait_modem_status(serial, arg);
		break;
	default:
		ret = -ENOIOCTLCMD;
		break;
	}
	return ret;
}