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
struct tty_struct {int /*<<< orphan*/  name; struct isi_port* driver_data; } ;
struct isi_port {int channel; struct isi_board* card; } ;
struct isi_board {int port_status; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ isicom_paranoia_check (struct isi_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void isicom_throttle(struct tty_struct *tty)
{
	struct isi_port *port = tty->driver_data;
	struct isi_board *card = port->card;

	if (isicom_paranoia_check(port, tty->name, "isicom_throttle"))
		return;

	/* tell the card that this port cannot handle any more data for now */
	card->port_status &= ~(1 << port->channel);
	outw(card->port_status, card->base + 0x02);
}