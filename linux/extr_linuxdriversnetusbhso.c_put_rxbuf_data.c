#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {int actual_length; int /*<<< orphan*/  transfer_buffer; } ;
struct tty_struct {int dummy; } ;
struct hso_serial {scalar_t__* rx_urb_filled; TYPE_2__* parent; int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__* usb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hso_dbg (int,char*) ; 
 size_t hso_urb_to_index (struct hso_serial*,struct urb*) ; 
 int tty_buffer_request_room (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 scalar_t__ tty_throttled (struct tty_struct*) ; 

__attribute__((used)) static int put_rxbuf_data(struct urb *urb, struct hso_serial *serial)
{
	struct tty_struct *tty;
	int count;

	/* Sanity check */
	if (urb == NULL || serial == NULL) {
		hso_dbg(0x1, "serial = NULL\n");
		return -2;
	}

	tty = tty_port_tty_get(&serial->port);

	if (tty && tty_throttled(tty)) {
		tty_kref_put(tty);
		return -1;
	}

	/* Push data to tty */
	hso_dbg(0x1, "data to push to tty\n");
	count = tty_buffer_request_room(&serial->port, urb->actual_length);
	if (count >= urb->actual_length) {
		tty_insert_flip_string(&serial->port, urb->transfer_buffer,
				       urb->actual_length);
		tty_flip_buffer_push(&serial->port);
	} else {
		dev_warn(&serial->parent->usb->dev,
			 "dropping data, %d bytes lost\n", urb->actual_length);
	}

	tty_kref_put(tty);

	serial->rx_urb_filled[hso_urb_to_index(serial, urb)] = 0;

	return 0;
}