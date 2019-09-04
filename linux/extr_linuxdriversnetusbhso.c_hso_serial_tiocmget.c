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
typedef  int u16 ;
struct tty_struct {struct hso_serial* driver_data; } ;
struct hso_tiocmget {int /*<<< orphan*/  prev_UART_state_bitmap; } ;
struct hso_serial {int /*<<< orphan*/  serial_lock; struct hso_tiocmget* tiocmget; scalar_t__ dtr_state; scalar_t__ rts_state; } ;

/* Variables and functions */
 int B_RING_SIGNAL ; 
 int B_RX_CARRIER ; 
 int B_TX_CARRIER ; 
 int EINVAL ; 
 int TIOCM_CD ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RNG ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  hso_dbg (int,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hso_serial_tiocmget(struct tty_struct *tty)
{
	int retval;
	struct hso_serial *serial = tty->driver_data;
	struct hso_tiocmget  *tiocmget;
	u16 UART_state_bitmap;

	/* sanity check */
	if (!serial) {
		hso_dbg(0x1, "no tty structures\n");
		return -EINVAL;
	}
	spin_lock_irq(&serial->serial_lock);
	retval = ((serial->rts_state) ? TIOCM_RTS : 0) |
	    ((serial->dtr_state) ? TIOCM_DTR : 0);
	tiocmget = serial->tiocmget;
	if (tiocmget) {

		UART_state_bitmap = le16_to_cpu(
			tiocmget->prev_UART_state_bitmap);
		if (UART_state_bitmap & B_RING_SIGNAL)
			retval |=  TIOCM_RNG;
		if (UART_state_bitmap & B_RX_CARRIER)
			retval |=  TIOCM_CD;
		if (UART_state_bitmap & B_TX_CARRIER)
			retval |=  TIOCM_DSR;
	}
	spin_unlock_irq(&serial->serial_lock);
	return retval;
}