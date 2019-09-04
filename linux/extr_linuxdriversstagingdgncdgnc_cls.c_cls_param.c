#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int uint ;
struct un_t {scalar_t__ un_type; struct channel_t* un_ch; } ;
struct tty_struct {scalar_t__ driver_data; } ;
struct dgnc_board {int bd_dividend; } ;
struct TYPE_8__ {int digi_flags; } ;
struct TYPE_6__ {int un_flags; int /*<<< orphan*/  un_tty; } ;
struct TYPE_5__ {int /*<<< orphan*/  un_tty; } ;
struct channel_t {int ch_c_cflag; int ch_flags; int ch_mostat; int ch_old_baud; int ch_custom_speed; int ch_c_iflag; scalar_t__ ch_startc; scalar_t__ ch_stopc; TYPE_3__* ch_cls_uart; TYPE_4__ ch_digi; struct dgnc_board* ch_bd; TYPE_2__ ch_tun; TYPE_1__ ch_pun; scalar_t__ ch_w_tail; scalar_t__ ch_w_head; scalar_t__ ch_e_tail; scalar_t__ ch_e_head; scalar_t__ ch_r_tail; scalar_t__ ch_r_head; } ;
struct TYPE_7__ {int /*<<< orphan*/  msr; int /*<<< orphan*/  ier; int /*<<< orphan*/  lcr; int /*<<< orphan*/  txrx; } ;

/* Variables and functions */
 int CBAUD ; 
 int CBAUDEX ; 
 int CH_BAUD0 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int CTSPACE ; 
 int C_BAUD (int /*<<< orphan*/ ) ; 
 scalar_t__ DGNC_PRINT ; 
 int DIGI_DTR_TOGGLE ; 
 int DIGI_FAST ; 
 int DIGI_FORCEDCD ; 
 int DIGI_RTS_TOGGLE ; 
 int IXOFF ; 
 int IXON ; 
 int PARENB ; 
 int PARODD ; 
 int RTSPACE ; 
 unsigned char UART_IER_MSI ; 
 unsigned char UART_IER_RDI ; 
 unsigned char UART_IER_RLSI ; 
 unsigned char UART_IER_THRI ; 
 unsigned char UART_LCR_DLAB ; 
 unsigned char UART_LCR_EPAR ; 
 unsigned char UART_LCR_PARITY ; 
 unsigned char UART_LCR_STOP ; 
 unsigned char UART_LCR_WLEN5 ; 
 unsigned char UART_LCR_WLEN6 ; 
 unsigned char UART_LCR_WLEN7 ; 
 unsigned char UART_LCR_WLEN8 ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int UN_ISOPEN ; 
 scalar_t__ _POSIX_VDISABLE ; 
 int /*<<< orphan*/  cls_assert_modem_signals (struct channel_t*) ; 
 int /*<<< orphan*/  cls_flush_uart_read (struct channel_t*) ; 
 int /*<<< orphan*/  cls_flush_uart_write (struct channel_t*) ; 
 int /*<<< orphan*/  cls_parse_modem (struct channel_t*,unsigned char) ; 
 int /*<<< orphan*/  cls_set_cts_flow_control (struct channel_t*) ; 
 int /*<<< orphan*/  cls_set_ixoff_flow_control (struct channel_t*) ; 
 int /*<<< orphan*/  cls_set_ixon_flow_control (struct channel_t*) ; 
 int /*<<< orphan*/  cls_set_no_input_flow_control (struct channel_t*) ; 
 int /*<<< orphan*/  cls_set_no_output_flow_control (struct channel_t*) ; 
 int /*<<< orphan*/  cls_set_rts_flow_control (struct channel_t*) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_param(struct tty_struct *tty)
{
	unsigned char lcr = 0;
	unsigned char uart_lcr = 0;
	unsigned char ier = 0;
	unsigned char uart_ier = 0;
	uint baud = 9600;
	int quot = 0;
	struct dgnc_board *bd;
	struct channel_t *ch;
	struct un_t   *un;

	if (!tty)
		return;

	un = (struct un_t *)tty->driver_data;
	if (!un)
		return;

	ch = un->un_ch;
	if (!ch)
		return;

	bd = ch->ch_bd;
	if (!bd)
		return;

	/* If baud rate is zero, flush queues, and set mval to drop DTR. */
	if ((ch->ch_c_cflag & (CBAUD)) == 0) {
		ch->ch_r_head = 0;
		ch->ch_r_tail = 0;
		ch->ch_e_head = 0;
		ch->ch_e_tail = 0;
		ch->ch_w_head = 0;
		ch->ch_w_tail = 0;

		cls_flush_uart_write(ch);
		cls_flush_uart_read(ch);

		/* The baudrate is B0 so all modem lines are to be dropped. */
		ch->ch_flags |= (CH_BAUD0);
		ch->ch_mostat &= ~(UART_MCR_RTS | UART_MCR_DTR);
		cls_assert_modem_signals(ch);
		ch->ch_old_baud = 0;
		return;
	} else if (ch->ch_custom_speed) {
		baud = ch->ch_custom_speed;
		/* Handle transition from B0 */
		if (ch->ch_flags & CH_BAUD0) {
			ch->ch_flags &= ~(CH_BAUD0);

			/*
			 * Bring back up RTS and DTR...
			 * Also handle RTS or DTR toggle if set.
			 */
			if (!(ch->ch_digi.digi_flags & DIGI_RTS_TOGGLE))
				ch->ch_mostat |= (UART_MCR_RTS);
			if (!(ch->ch_digi.digi_flags & DIGI_DTR_TOGGLE))
				ch->ch_mostat |= (UART_MCR_DTR);
		}

	} else {
		int iindex = 0;
		int jindex = 0;

		ulong bauds[4][16] = {
			{ /* slowbaud */
				0,      50,     75,     110,
				134,    150,    200,    300,
				600,    1200,   1800,   2400,
				4800,   9600,   19200,  38400 },
			{ /* slowbaud & CBAUDEX */
				0,      57600,  115200, 230400,
				460800, 150,    200,    921600,
				600,    1200,   1800,   2400,
				4800,   9600,   19200,  38400 },
			{ /* fastbaud */
				0,      57600,   76800, 115200,
				131657, 153600, 230400, 460800,
				921600, 1200,   1800,   2400,
				4800,   9600,   19200,  38400 },
			{ /* fastbaud & CBAUDEX */
				0,      57600,  115200, 230400,
				460800, 150,    200,    921600,
				600,    1200,   1800,   2400,
				4800,   9600,   19200,  38400 }
		};

		/*
		 * Only use the TXPrint baud rate if the terminal
		 * unit is NOT open
		 */
		if (!(ch->ch_tun.un_flags & UN_ISOPEN) &&
		    (un->un_type == DGNC_PRINT))
			baud = C_BAUD(ch->ch_pun.un_tty) & 0xff;
		else
			baud = C_BAUD(ch->ch_tun.un_tty) & 0xff;

		if (ch->ch_c_cflag & CBAUDEX)
			iindex = 1;

		if (ch->ch_digi.digi_flags & DIGI_FAST)
			iindex += 2;

		jindex = baud;

		if ((iindex >= 0) && (iindex < 4) && (jindex >= 0) &&
		    (jindex < 16)) {
			baud = bauds[iindex][jindex];
		} else {
			baud = 0;
		}

		if (baud == 0)
			baud = 9600;

		/* Handle transition from B0 */
		if (ch->ch_flags & CH_BAUD0) {
			ch->ch_flags &= ~(CH_BAUD0);

			/*
			 * Bring back up RTS and DTR...
			 * Also handle RTS or DTR toggle if set.
			 */
			if (!(ch->ch_digi.digi_flags & DIGI_RTS_TOGGLE))
				ch->ch_mostat |= (UART_MCR_RTS);
			if (!(ch->ch_digi.digi_flags & DIGI_DTR_TOGGLE))
				ch->ch_mostat |= (UART_MCR_DTR);
		}
	}

	if (ch->ch_c_cflag & PARENB)
		lcr |= UART_LCR_PARITY;

	if (!(ch->ch_c_cflag & PARODD))
		lcr |= UART_LCR_EPAR;

#ifdef CMSPAR
	if (ch->ch_c_cflag & CMSPAR)
		lcr |= UART_LCR_SPAR;
#endif

	if (ch->ch_c_cflag & CSTOPB)
		lcr |= UART_LCR_STOP;

	switch (ch->ch_c_cflag & CSIZE) {
	case CS5:
		lcr |= UART_LCR_WLEN5;
		break;
	case CS6:
		lcr |= UART_LCR_WLEN6;
		break;
	case CS7:
		lcr |= UART_LCR_WLEN7;
		break;
	case CS8:
	default:
		lcr |= UART_LCR_WLEN8;
		break;
	}

	uart_ier = readb(&ch->ch_cls_uart->ier);
	ier =  uart_ier;
	uart_lcr = readb(&ch->ch_cls_uart->lcr);

	if (baud == 0)
		baud = 9600;

	quot = ch->ch_bd->bd_dividend / baud;

	if (quot != 0 && ch->ch_old_baud != baud) {
		ch->ch_old_baud = baud;
		writeb(UART_LCR_DLAB, &ch->ch_cls_uart->lcr);
		writeb((quot & 0xff), &ch->ch_cls_uart->txrx);
		writeb((quot >> 8), &ch->ch_cls_uart->ier);
		writeb(lcr, &ch->ch_cls_uart->lcr);
	}

	if (uart_lcr != lcr)
		writeb(lcr, &ch->ch_cls_uart->lcr);

	if (ch->ch_c_cflag & CREAD)
		ier |= (UART_IER_RDI | UART_IER_RLSI);
	else
		ier &= ~(UART_IER_RDI | UART_IER_RLSI);

	/*
	 * Have the UART interrupt on modem signal changes ONLY when
	 * we are in hardware flow control mode, or CLOCAL/FORCEDCD is not set.
	 */
	if ((ch->ch_digi.digi_flags & CTSPACE) ||
	    (ch->ch_digi.digi_flags & RTSPACE) ||
	    (ch->ch_c_cflag & CRTSCTS) ||
	    !(ch->ch_digi.digi_flags & DIGI_FORCEDCD) ||
	    !(ch->ch_c_cflag & CLOCAL))
		ier |= UART_IER_MSI;
	else
		ier &= ~UART_IER_MSI;

	ier |= UART_IER_THRI;

	if (ier != uart_ier)
		writeb(ier, &ch->ch_cls_uart->ier);

	if (ch->ch_digi.digi_flags & CTSPACE || ch->ch_c_cflag & CRTSCTS) {
		cls_set_cts_flow_control(ch);
	} else if (ch->ch_c_iflag & IXON) {
		if ((ch->ch_startc == _POSIX_VDISABLE) ||
		    (ch->ch_stopc == _POSIX_VDISABLE))
			cls_set_no_output_flow_control(ch);
		else
			cls_set_ixon_flow_control(ch);
	} else {
		cls_set_no_output_flow_control(ch);
	}

	if (ch->ch_digi.digi_flags & RTSPACE || ch->ch_c_cflag & CRTSCTS) {
		cls_set_rts_flow_control(ch);
	} else if (ch->ch_c_iflag & IXOFF) {
		if ((ch->ch_startc == _POSIX_VDISABLE) ||
		    (ch->ch_stopc == _POSIX_VDISABLE))
			cls_set_no_input_flow_control(ch);
		else
			cls_set_ixoff_flow_control(ch);
	} else {
		cls_set_no_input_flow_control(ch);
	}

	cls_assert_modem_signals(ch);

	cls_parse_modem(ch, readb(&ch->ch_cls_uart->msr));
}