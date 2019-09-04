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
struct tty_struct {struct gb_tty* driver_data; } ;
struct gb_tty {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  close_pending; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  write_fifo; } ;

/* Variables and functions */
 int kfifo_in_spinlocked (int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_tty_write(struct tty_struct *tty, const unsigned char *buf,
			int count)
{
	struct gb_tty *gb_tty = tty->driver_data;

	count =  kfifo_in_spinlocked(&gb_tty->write_fifo, buf, count,
				     &gb_tty->write_lock);
	if (count && !gb_tty->close_pending)
		schedule_work(&gb_tty->tx_work);

	return count;
}