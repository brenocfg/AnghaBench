#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {unsigned long c_cflag; } ;
struct tty_struct {TYPE_1__ termios; struct isi_port* driver_data; } ;
struct TYPE_5__ {int flags; } ;
struct isi_port {int channel; TYPE_2__ port; struct isi_board* card; } ;
struct isi_board {unsigned long base; int shift_count; int port_status; } ;

/* Variables and functions */
 int ASYNC_SPD_HI ; 
 int ASYNC_SPD_MASK ; 
 int ASYNC_SPD_SHI ; 
 int ASYNC_SPD_VHI ; 
 int ASYNC_SPD_WARP ; 
 unsigned long CBAUDEX ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned long C_BAUD (struct tty_struct*) ; 
 int /*<<< orphan*/  C_CLOCAL (struct tty_struct*) ; 
 scalar_t__ C_CREAD (struct tty_struct*) ; 
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 int C_CSIZE (struct tty_struct*) ; 
 scalar_t__ C_CSTOPB (struct tty_struct*) ; 
 scalar_t__ C_PARENB (struct tty_struct*) ; 
 scalar_t__ C_PARODD (struct tty_struct*) ; 
 int ISICOM_2SB ; 
 int ISICOM_CS5 ; 
 int ISICOM_CS6 ; 
 int ISICOM_CS7 ; 
 int ISICOM_CS8 ; 
 unsigned char ISICOM_CTSRTS ; 
 int ISICOM_EVPAR ; 
 unsigned char ISICOM_INITIATE_XONXOFF ; 
 int ISICOM_ODPAR ; 
 unsigned char ISICOM_RESPOND_XONXOFF ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 int /*<<< orphan*/  InterruptTheCard (unsigned long) ; 
 int START_CHAR (struct tty_struct*) ; 
 int STOP_CHAR (struct tty_struct*) ; 
 scalar_t__ WaitTillCardIsFree (unsigned long) ; 
 int /*<<< orphan*/  drop_dtr (struct isi_port*) ; 
 int* linuxb_to_isib ; 
 int /*<<< orphan*/  outw (int,unsigned long) ; 
 int /*<<< orphan*/  raise_dtr (struct isi_port*) ; 
 int /*<<< orphan*/  tty_port_set_check_carrier (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tty_port_set_cts_flow (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void isicom_config_port(struct tty_struct *tty)
{
	struct isi_port *port = tty->driver_data;
	struct isi_board *card = port->card;
	unsigned long baud;
	unsigned long base = card->base;
	u16 channel_setup, channel = port->channel,
		shift_count = card->shift_count;
	unsigned char flow_ctrl;

	/* FIXME: Switch to new tty baud API */
	baud = C_BAUD(tty);
	if (baud & CBAUDEX) {
		baud &= ~CBAUDEX;

		/*  if CBAUDEX bit is on and the baud is set to either 50 or 75
		 *  then the card is programmed for 57.6Kbps or 115Kbps
		 *  respectively.
		 */

		/* 1,2,3,4 => 57.6, 115.2, 230, 460 kbps resp. */
		if (baud < 1 || baud > 4)
			tty->termios.c_cflag &= ~CBAUDEX;
		else
			baud += 15;
	}
	if (baud == 15) {

		/*  the ASYNC_SPD_HI and ASYNC_SPD_VHI options are set
		 *  by the set_serial_info ioctl ... this is done by
		 *  the 'setserial' utility.
		 */

		if ((port->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_HI)
			baud++; /*  57.6 Kbps */
		if ((port->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_VHI)
			baud += 2; /*  115  Kbps */
		if ((port->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_SHI)
			baud += 3; /* 230 kbps*/
		if ((port->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_WARP)
			baud += 4; /* 460 kbps*/
	}
	if (linuxb_to_isib[baud] == -1) {
		/* hang up */
		drop_dtr(port);
		return;
	} else
		raise_dtr(port);

	if (WaitTillCardIsFree(base) == 0) {
		outw(0x8000 | (channel << shift_count) | 0x03, base);
		outw(linuxb_to_isib[baud] << 8 | 0x03, base);
		channel_setup = 0;
		switch (C_CSIZE(tty)) {
		case CS5:
			channel_setup |= ISICOM_CS5;
			break;
		case CS6:
			channel_setup |= ISICOM_CS6;
			break;
		case CS7:
			channel_setup |= ISICOM_CS7;
			break;
		case CS8:
			channel_setup |= ISICOM_CS8;
			break;
		}

		if (C_CSTOPB(tty))
			channel_setup |= ISICOM_2SB;
		if (C_PARENB(tty)) {
			channel_setup |= ISICOM_EVPAR;
			if (C_PARODD(tty))
				channel_setup |= ISICOM_ODPAR;
		}
		outw(channel_setup, base);
		InterruptTheCard(base);
	}
	tty_port_set_check_carrier(&port->port, !C_CLOCAL(tty));

	/* flow control settings ...*/
	flow_ctrl = 0;
	tty_port_set_cts_flow(&port->port, C_CRTSCTS(tty));
	if (C_CRTSCTS(tty))
		flow_ctrl |= ISICOM_CTSRTS;
	if (I_IXON(tty))
		flow_ctrl |= ISICOM_RESPOND_XONXOFF;
	if (I_IXOFF(tty))
		flow_ctrl |= ISICOM_INITIATE_XONXOFF;

	if (WaitTillCardIsFree(base) == 0) {
		outw(0x8000 | (channel << shift_count) | 0x04, base);
		outw(flow_ctrl << 8 | 0x05, base);
		outw((STOP_CHAR(tty)) << 8 | (START_CHAR(tty)), base);
		InterruptTheCard(base);
	}

	/*	rx enabled -> enable port for rx on the card	*/
	if (C_CREAD(tty)) {
		card->port_status |= (1 << channel);
		outw(card->port_status, base + 0x02);
	}
}