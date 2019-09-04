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
struct hso_serial {int tx_buffer_count; int /*<<< orphan*/  serial_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hso_serial_chars_in_buffer(struct tty_struct *tty)
{
	struct hso_serial *serial = tty->driver_data;
	int chars;
	unsigned long flags;

	/* sanity check */
	if (serial == NULL)
		return 0;

	spin_lock_irqsave(&serial->serial_lock, flags);
	chars = serial->tx_buffer_count;
	spin_unlock_irqrestore(&serial->serial_lock, flags);

	return chars;
}