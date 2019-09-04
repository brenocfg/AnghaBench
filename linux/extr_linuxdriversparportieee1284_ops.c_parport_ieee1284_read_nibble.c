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

size_t parport_ieee1284_read_nibble (struct parport *port, 
				     void *buffer, size_t len,
				     int flags)
{
#ifndef CONFIG_PARPORT_1284
	return 0;
#else
	unsigned char *buf = buffer;
	int i;
	unsigned char byte = 0;

	len *= 2; /* in nibbles */
	for (i=0; i < len; i++) {
		unsigned char nibble;

		/* Does the error line indicate end of data? */
		if (((i & 1) == 0) &&
		    (parport_read_status(port) & PARPORT_STATUS_ERROR)) {
			goto end_of_data;
		}

		/* Event 7: Set nAutoFd low. */
		parport_frob_control (port,
				      PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		/* Event 9: nAck goes low. */
		port->ieee1284.phase = IEEE1284_PH_REV_DATA;
		if (parport_wait_peripheral (port,
					     PARPORT_STATUS_ACK, 0)) {
			/* Timeout -- no more data? */
			DPRINTK (KERN_DEBUG
				 "%s: Nibble timeout at event 9 (%d bytes)\n",
				 port->name, i/2);
			parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);
			break;
		}


		/* Read a nibble. */
		nibble = parport_read_status (port) >> 3;
		nibble &= ~8;
		if ((nibble & 0x10) == 0)
			nibble |= 8;
		nibble &= 0xf;

		/* Event 10: Set nAutoFd high. */
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);

		/* Event 11: nAck goes high. */
		if (parport_wait_peripheral (port,
					     PARPORT_STATUS_ACK,
					     PARPORT_STATUS_ACK)) {
			/* Timeout -- no more data? */
			DPRINTK (KERN_DEBUG
				 "%s: Nibble timeout at event 11\n",
				 port->name);
			break;
		}

		if (i & 1) {
			/* Second nibble */
			byte |= nibble << 4;
			*buf++ = byte;
		} else 
			byte = nibble;
	}

	if (i == len) {
		/* Read the last nibble without checking data avail. */
		if (parport_read_status (port) & PARPORT_STATUS_ERROR) {
		end_of_data:
			DPRINTK (KERN_DEBUG
				"%s: No more nibble data (%d bytes)\n",
				port->name, i/2);

			/* Go to reverse idle phase. */
			parport_frob_control (port,
					      PARPORT_CONTROL_AUTOFD,
					      PARPORT_CONTROL_AUTOFD);
			port->physport->ieee1284.phase = IEEE1284_PH_REV_IDLE;
		}
		else
			port->physport->ieee1284.phase = IEEE1284_PH_HBUSY_DAVAIL;
	}

	return i/2;
#endif /* IEEE1284 support */
}