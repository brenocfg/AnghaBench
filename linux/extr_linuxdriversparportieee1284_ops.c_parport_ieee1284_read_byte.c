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
struct parport {int dummy; } ;

/* Variables and functions */

size_t parport_ieee1284_read_byte (struct parport *port,
				   void *buffer, size_t len,
				   int flags)
{
#ifndef CONFIG_PARPORT_1284
	return 0;
#else
	unsigned char *buf = buffer;
	ssize_t count = 0;

	for (count = 0; count < len; count++) {
		unsigned char byte;

		/* Data available? */
		if (parport_read_status (port) & PARPORT_STATUS_ERROR) {
			goto end_of_data;
		}

		/* Event 14: Place data bus in high impedance state. */
		parport_data_reverse (port);

		/* Event 7: Set nAutoFd low. */
		parport_frob_control (port,
				      PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		/* Event 9: nAck goes low. */
		port->physport->ieee1284.phase = IEEE1284_PH_REV_DATA;
		if (parport_wait_peripheral (port,
					     PARPORT_STATUS_ACK,
					     0)) {
			/* Timeout -- no more data? */
			parport_frob_control (port, PARPORT_CONTROL_AUTOFD,
						 0);
			DPRINTK (KERN_DEBUG "%s: Byte timeout at event 9\n",
				 port->name);
			break;
		}

		byte = parport_read_data (port);
		*buf++ = byte;

		/* Event 10: Set nAutoFd high */
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);

		/* Event 11: nAck goes high. */
		if (parport_wait_peripheral (port,
					     PARPORT_STATUS_ACK,
					     PARPORT_STATUS_ACK)) {
			/* Timeout -- no more data? */
			DPRINTK (KERN_DEBUG "%s: Byte timeout at event 11\n",
				 port->name);
			break;
		}

		/* Event 16: Set nStrobe low. */
		parport_frob_control (port,
				      PARPORT_CONTROL_STROBE,
				      PARPORT_CONTROL_STROBE);
		udelay (5);

		/* Event 17: Set nStrobe high. */
		parport_frob_control (port, PARPORT_CONTROL_STROBE, 0);
	}

	if (count == len) {
		/* Read the last byte without checking data avail. */
		if (parport_read_status (port) & PARPORT_STATUS_ERROR) {
		end_of_data:
			DPRINTK (KERN_DEBUG
				 "%s: No more byte data (%zd bytes)\n",
				 port->name, count);

			/* Go to reverse idle phase. */
			parport_frob_control (port,
					      PARPORT_CONTROL_AUTOFD,
					      PARPORT_CONTROL_AUTOFD);
			port->physport->ieee1284.phase = IEEE1284_PH_REV_IDLE;
		}
		else
			port->physport->ieee1284.phase = IEEE1284_PH_HBUSY_DAVAIL;
	}

	return count;
#endif /* IEEE1284 support */
}