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
struct tty_struct {int dummy; } ;
struct gbphy_device {int dummy; } ;
struct gb_tty {int disconnected; struct gb_tty* buffer; int /*<<< orphan*/  write_fifo; int /*<<< orphan*/  port; int /*<<< orphan*/  minor; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wioctl; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable_rx (struct gb_connection*) ; 
 struct gb_tty* gb_gbphy_get_data (struct gbphy_device*) ; 
 int /*<<< orphan*/  gb_tty_driver ; 
 int /*<<< orphan*/  gbphy_runtime_get_noresume (struct gbphy_device*) ; 
 int gbphy_runtime_get_sync (struct gbphy_device*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gb_tty*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_minor (struct gb_tty*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_vhangup (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_uart_remove(struct gbphy_device *gbphy_dev)
{
	struct gb_tty *gb_tty = gb_gbphy_get_data(gbphy_dev);
	struct gb_connection *connection = gb_tty->connection;
	struct tty_struct *tty;
	int ret;

	ret = gbphy_runtime_get_sync(gbphy_dev);
	if (ret)
		gbphy_runtime_get_noresume(gbphy_dev);

	mutex_lock(&gb_tty->mutex);
	gb_tty->disconnected = true;

	wake_up_all(&gb_tty->wioctl);
	mutex_unlock(&gb_tty->mutex);

	tty = tty_port_tty_get(&gb_tty->port);
	if (tty) {
		tty_vhangup(tty);
		tty_kref_put(tty);
	}

	gb_connection_disable_rx(connection);
	tty_unregister_device(gb_tty_driver, gb_tty->minor);

	/* FIXME - free transmit / receive buffers */

	gb_connection_disable(connection);
	tty_port_destroy(&gb_tty->port);
	gb_connection_destroy(connection);
	release_minor(gb_tty);
	kfifo_free(&gb_tty->write_fifo);
	kfree(gb_tty->buffer);
	kfree(gb_tty);
}