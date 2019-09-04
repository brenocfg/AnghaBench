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

size_t parport_ieee1284_ecp_read_data (struct parport *port,
				       void *buffer, size_t len, int flags)
{
#ifndef CONFIG_PARPORT_1284
	return 0;
#else
	struct pardevice *dev = port->cad;
	unsigned char *buf = buffer;
	int rle_count = 0; /* shut gcc up */
	unsigned char ctl;
	int rle = 0;
	ssize_t count = 0;

	port = port->physport;

	if (port->ieee1284.phase != IEEE1284_PH_REV_IDLE)
		if (ecp_forward_to_reverse (port))
			return 0;

	port->ieee1284.phase = IEEE1284_PH_REV_DATA;

	/* Set HostAck low to start accepting data. */
	ctl = parport_read_control (port);
	ctl &= ~(PARPORT_CONTROL_STROBE | PARPORT_CONTROL_INIT |
		 PARPORT_CONTROL_AUTOFD);
	parport_write_control (port,
			       ctl | PARPORT_CONTROL_AUTOFD);
	while (count < len) {
		unsigned long expire = jiffies + dev->timeout;
		unsigned char byte;
		int command;

		/* Event 43: Peripheral sets nAck low. It can take as
                   long as it wants. */
		while (parport_wait_peripheral (port, PARPORT_STATUS_ACK, 0)) {
			/* The peripheral hasn't given us data in
			   35ms.  If we have data to give back to the
			   caller, do it now. */
			if (count)
				goto out;

			/* If we've used up all the time we were allowed,
			   give up altogether. */
			if (!time_before (jiffies, expire))
				goto out;

			/* Yield the port for a while. */
			if (count && dev->port->irq != PARPORT_IRQ_NONE) {
				parport_release (dev);
				schedule_timeout_interruptible(msecs_to_jiffies(40));
				parport_claim_or_block (dev);
			}
			else
				/* We must have the device claimed here. */
				parport_wait_event (port, msecs_to_jiffies(40));

			/* Is there a signal pending? */
			if (signal_pending (current))
				goto out;
		}

		/* Is this a command? */
		if (rle)
			/* The last byte was a run-length count, so
                           this can't be as well. */
			command = 0;
		else
			command = (parport_read_status (port) &
				   PARPORT_STATUS_BUSY) ? 1 : 0;

		/* Read the data. */
		byte = parport_read_data (port);

		/* If this is a channel command, rather than an RLE
                   command or a normal data byte, don't accept it. */
		if (command) {
			if (byte & 0x80) {
				DPRINTK (KERN_DEBUG "%s: stopping short at "
					 "channel command (%02x)\n",
					 port->name, byte);
				goto out;
			}
			else if (port->ieee1284.mode != IEEE1284_MODE_ECPRLE)
				DPRINTK (KERN_DEBUG "%s: device illegally "
					 "using RLE; accepting anyway\n",
					 port->name);

			rle_count = byte + 1;

			/* Are we allowed to read that many bytes? */
			if (rle_count > (len - count)) {
				DPRINTK (KERN_DEBUG "%s: leaving %d RLE bytes "
					 "for next time\n", port->name,
					 rle_count);
				break;
			}

			rle = 1;
		}

		/* Event 44: Set HostAck high, acknowledging handshake. */
		parport_write_control (port, ctl);

		/* Event 45: The peripheral has 35ms to set nAck high. */
		if (parport_wait_peripheral (port, PARPORT_STATUS_ACK,
					     PARPORT_STATUS_ACK)) {
			/* It's gone wrong.  Return what data we have
                           to the caller. */
			DPRINTK (KERN_DEBUG "ECP read timed out at 45\n");

			if (command)
				printk (KERN_WARNING
					"%s: command ignored (%02x)\n",
					port->name, byte);

			break;
		}

		/* Event 46: Set HostAck low and accept the data. */
		parport_write_control (port,
				       ctl | PARPORT_CONTROL_AUTOFD);

		/* If we just read a run-length count, fetch the data. */
		if (command)
			continue;

		/* If this is the byte after a run-length count, decompress. */
		if (rle) {
			rle = 0;
			memset (buf, byte, rle_count);
			buf += rle_count;
			count += rle_count;
			DPRINTK (KERN_DEBUG "%s: decompressed to %d bytes\n",
				 port->name, rle_count);
		} else {
			/* Normal data byte. */
			*buf = byte;
			buf++, count++;
		}
	}

 out:
	port->ieee1284.phase = IEEE1284_PH_REV_IDLE;
	return count;
#endif /* IEEE1284 support */
}