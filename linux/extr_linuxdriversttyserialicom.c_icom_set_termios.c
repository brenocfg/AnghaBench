#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  lock; } ;
struct ktermios {unsigned int c_cflag; unsigned int c_iflag; } ;
struct TYPE_11__ {int read_status_mask; int ignore_status_mask; TYPE_2__* dram; scalar_t__ xmitRestart_pci; scalar_t__* xmitRestart; scalar_t__ put_length; scalar_t__ next_rcv; scalar_t__ statStg_pci; TYPE_4__* statStg; } ;
struct TYPE_10__ {TYPE_3__* rcv; TYPE_1__* xmit; } ;
struct TYPE_9__ {unsigned short WorkingLength; scalar_t__ leLength; scalar_t__ flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  CmdReg; int /*<<< orphan*/  XmitStatusAddr; int /*<<< orphan*/  RcvStatusAddr; int /*<<< orphan*/  ier; int /*<<< orphan*/  FlagFillIdleTimer; int /*<<< orphan*/  HDLCConfigReg; int /*<<< orphan*/  async_config2; int /*<<< orphan*/  async_config3; int /*<<< orphan*/  PrevCmdReg; } ;
struct TYPE_7__ {scalar_t__ flags; } ;

/* Variables and functions */
 size_t BAUD_TABLE_LIMIT ; 
 unsigned int BRKINT ; 
 int CMD_RCV_DISABLE ; 
 int CMD_RESTART ; 
 int CMD_XMIT_RCV_ENABLE ; 
 unsigned int CREAD ; 
 unsigned int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 char HDLC_FF_FILL ; 
 char HDLC_HDW_FLOW ; 
 char HDLC_PPP_PURE_ASYNC ; 
 char ICOM_ACFG_2STOP_BIT ; 
 char ICOM_ACFG_5BPC ; 
 char ICOM_ACFG_6BPC ; 
 char ICOM_ACFG_7BPC ; 
 char ICOM_ACFG_8BPC ; 
 char ICOM_ACFG_DRIVE1 ; 
 char ICOM_ACFG_PARITY_ENAB ; 
 char ICOM_ACFG_PARITY_ODD ; 
 TYPE_5__* ICOM_PORT ; 
 unsigned int IGNBRK ; 
 unsigned int IGNPAR ; 
 unsigned int INPCK ; 
 int NUM_RBUFFS ; 
 int NUM_XBUFFS ; 
 unsigned int PARENB ; 
 unsigned int PARMRK ; 
 unsigned int PARODD ; 
 int /*<<< orphan*/  RCV_BUFF_SZ ; 
 int SA_FLAGS_BREAK_DET ; 
 int SA_FLAGS_FRAME_ERROR ; 
 int SA_FLAGS_OVERRUN ; 
 int SA_FLAGS_PARITY_ERROR ; 
 int SA_FL_RCV_DONE ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int* icom_acfg_baud ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,unsigned int,int) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icom_set_termios(struct uart_port *port,
			     struct ktermios *termios,
			     struct ktermios *old_termios)
{
	int baud;
	unsigned cflag, iflag;
	char new_config2;
	char new_config3 = 0;
	char tmp_byte;
	int index;
	int rcv_buff, xmit_buff;
	unsigned long offset;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	trace(ICOM_PORT, "CHANGE_SPEED", 0);

	cflag = termios->c_cflag;
	iflag = termios->c_iflag;

	new_config2 = ICOM_ACFG_DRIVE1;

	/* byte size and parity */
	switch (cflag & CSIZE) {
	case CS5:		/* 5 bits/char */
		new_config2 |= ICOM_ACFG_5BPC;
		break;
	case CS6:		/* 6 bits/char */
		new_config2 |= ICOM_ACFG_6BPC;
		break;
	case CS7:		/* 7 bits/char */
		new_config2 |= ICOM_ACFG_7BPC;
		break;
	case CS8:		/* 8 bits/char */
		new_config2 |= ICOM_ACFG_8BPC;
		break;
	default:
		break;
	}
	if (cflag & CSTOPB) {
		/* 2 stop bits */
		new_config2 |= ICOM_ACFG_2STOP_BIT;
	}
	if (cflag & PARENB) {
		/* parity bit enabled */
		new_config2 |= ICOM_ACFG_PARITY_ENAB;
		trace(ICOM_PORT, "PARENB", 0);
	}
	if (cflag & PARODD) {
		/* odd parity */
		new_config2 |= ICOM_ACFG_PARITY_ODD;
		trace(ICOM_PORT, "PARODD", 0);
	}

	/* Determine divisor based on baud rate */
	baud = uart_get_baud_rate(port, termios, old_termios,
				  icom_acfg_baud[0],
				  icom_acfg_baud[BAUD_TABLE_LIMIT]);
	if (!baud)
		baud = 9600;	/* B0 transition handled in rs_set_termios */

	for (index = 0; index < BAUD_TABLE_LIMIT; index++) {
		if (icom_acfg_baud[index] == baud) {
			new_config3 = index;
			break;
		}
	}

	uart_update_timeout(port, cflag, baud);

	/* CTS flow control flag and modem status interrupts */
	tmp_byte = readb(&(ICOM_PORT->dram->HDLCConfigReg));
	if (cflag & CRTSCTS)
		tmp_byte |= HDLC_HDW_FLOW;
	else
		tmp_byte &= ~HDLC_HDW_FLOW;
	writeb(tmp_byte, &(ICOM_PORT->dram->HDLCConfigReg));

	/*
	 * Set up parity check flag
	 */
	ICOM_PORT->read_status_mask = SA_FLAGS_OVERRUN | SA_FL_RCV_DONE;
	if (iflag & INPCK)
		ICOM_PORT->read_status_mask |=
		    SA_FLAGS_FRAME_ERROR | SA_FLAGS_PARITY_ERROR;

	if ((iflag & BRKINT) || (iflag & PARMRK))
		ICOM_PORT->read_status_mask |= SA_FLAGS_BREAK_DET;

	/*
	 * Characters to ignore
	 */
	ICOM_PORT->ignore_status_mask = 0;
	if (iflag & IGNPAR)
		ICOM_PORT->ignore_status_mask |=
		    SA_FLAGS_PARITY_ERROR | SA_FLAGS_FRAME_ERROR;
	if (iflag & IGNBRK) {
		ICOM_PORT->ignore_status_mask |= SA_FLAGS_BREAK_DET;
		/*
		 * If we're ignore parity and break indicators, ignore
		 * overruns too.  (For real raw support).
		 */
		if (iflag & IGNPAR)
			ICOM_PORT->ignore_status_mask |= SA_FLAGS_OVERRUN;
	}

	/*
	 * !!! ignore all characters if CREAD is not set
	 */
	if ((cflag & CREAD) == 0)
		ICOM_PORT->ignore_status_mask |= SA_FL_RCV_DONE;

	/* Turn off Receiver to prepare for reset */
	writeb(CMD_RCV_DISABLE, &ICOM_PORT->dram->CmdReg);

	for (index = 0; index < 10; index++) {
		if (readb(&ICOM_PORT->dram->PrevCmdReg) == 0x00) {
			break;
		}
	}

	/* clear all current buffers of data */
	for (rcv_buff = 0; rcv_buff < NUM_RBUFFS; rcv_buff++) {
		ICOM_PORT->statStg->rcv[rcv_buff].flags = 0;
		ICOM_PORT->statStg->rcv[rcv_buff].leLength = 0;
		ICOM_PORT->statStg->rcv[rcv_buff].WorkingLength =
		    (unsigned short int) cpu_to_le16(RCV_BUFF_SZ);
	}

	for (xmit_buff = 0; xmit_buff < NUM_XBUFFS; xmit_buff++) {
		ICOM_PORT->statStg->xmit[xmit_buff].flags = 0;
	}

	/* activate changes and start xmit and receiver here */
	/* Enable the receiver */
	writeb(new_config3, &(ICOM_PORT->dram->async_config3));
	writeb(new_config2, &(ICOM_PORT->dram->async_config2));
	tmp_byte = readb(&(ICOM_PORT->dram->HDLCConfigReg));
	tmp_byte |= HDLC_PPP_PURE_ASYNC | HDLC_FF_FILL;
	writeb(tmp_byte, &(ICOM_PORT->dram->HDLCConfigReg));
	writeb(0x04, &(ICOM_PORT->dram->FlagFillIdleTimer));	/* 0.5 seconds */
	writeb(0xFF, &(ICOM_PORT->dram->ier));	/* enable modem signal interrupts */

	/* reset processor */
	writeb(CMD_RESTART, &ICOM_PORT->dram->CmdReg);

	for (index = 0; index < 10; index++) {
		if (readb(&ICOM_PORT->dram->CmdReg) == 0x00) {
			break;
		}
	}

	/* Enable Transmitter and Receiver */
	offset =
	    (unsigned long) &ICOM_PORT->statStg->rcv[0] -
	    (unsigned long) ICOM_PORT->statStg;
	writel(ICOM_PORT->statStg_pci + offset,
	       &ICOM_PORT->dram->RcvStatusAddr);
	ICOM_PORT->next_rcv = 0;
	ICOM_PORT->put_length = 0;
	*ICOM_PORT->xmitRestart = 0;
	writel(ICOM_PORT->xmitRestart_pci,
	       &ICOM_PORT->dram->XmitStatusAddr);
	trace(ICOM_PORT, "XR_ENAB", 0);
	writeb(CMD_XMIT_RCV_ENABLE, &ICOM_PORT->dram->CmdReg);

	spin_unlock_irqrestore(&port->lock, flags);
}