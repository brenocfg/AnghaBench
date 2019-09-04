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
struct r_port {unsigned int ignore_status_mask; unsigned int read_status_mask; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  CHANNEL_t ;

/* Variables and functions */
 unsigned int RXBREAK ; 
 unsigned int RXFOVERFL ; 
 unsigned int RXFRAME ; 
 unsigned int RXPARITY ; 
 unsigned int STATMODE ; 
 unsigned int STMBREAKH ; 
 unsigned int STMFRAMEH ; 
 unsigned int STMPARITYH ; 
 unsigned int STMRCVROVRH ; 
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 int /*<<< orphan*/  sDisRxStatusMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sEnRxStatusMode (int /*<<< orphan*/ *) ; 
 int sGetRxCnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sGetTxRxDataIO (int /*<<< orphan*/ *) ; 
 unsigned char sInB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sInStrW (int /*<<< orphan*/ ,unsigned short*,int) ; 
 unsigned int sInW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ *,unsigned int,char) ; 
 int tty_prepare_flip_string (int /*<<< orphan*/ *,unsigned char**,int) ; 

__attribute__((used)) static void rp_do_receive(struct r_port *info, CHANNEL_t *cp,
		unsigned int ChanStatus)
{
	unsigned int CharNStat;
	int ToRecv, wRecv, space;
	unsigned char *cbuf;

	ToRecv = sGetRxCnt(cp);
#ifdef ROCKET_DEBUG_INTR
	printk(KERN_INFO "rp_do_receive(%d)...\n", ToRecv);
#endif
	if (ToRecv == 0)
		return;

	/*
	 * if status indicates there are errored characters in the
	 * FIFO, then enter status mode (a word in FIFO holds
	 * character and status).
	 */
	if (ChanStatus & (RXFOVERFL | RXBREAK | RXFRAME | RXPARITY)) {
		if (!(ChanStatus & STATMODE)) {
#ifdef ROCKET_DEBUG_RECEIVE
			printk(KERN_INFO "Entering STATMODE...\n");
#endif
			ChanStatus |= STATMODE;
			sEnRxStatusMode(cp);
		}
	}

	/* 
	 * if we previously entered status mode, then read down the
	 * FIFO one word at a time, pulling apart the character and
	 * the status.  Update error counters depending on status
	 */
	if (ChanStatus & STATMODE) {
#ifdef ROCKET_DEBUG_RECEIVE
		printk(KERN_INFO "Ignore %x, read %x...\n",
			info->ignore_status_mask, info->read_status_mask);
#endif
		while (ToRecv) {
			char flag;

			CharNStat = sInW(sGetTxRxDataIO(cp));
#ifdef ROCKET_DEBUG_RECEIVE
			printk(KERN_INFO "%x...\n", CharNStat);
#endif
			if (CharNStat & STMBREAKH)
				CharNStat &= ~(STMFRAMEH | STMPARITYH);
			if (CharNStat & info->ignore_status_mask) {
				ToRecv--;
				continue;
			}
			CharNStat &= info->read_status_mask;
			if (CharNStat & STMBREAKH)
				flag = TTY_BREAK;
			else if (CharNStat & STMPARITYH)
				flag = TTY_PARITY;
			else if (CharNStat & STMFRAMEH)
				flag = TTY_FRAME;
			else if (CharNStat & STMRCVROVRH)
				flag = TTY_OVERRUN;
			else
				flag = TTY_NORMAL;
			tty_insert_flip_char(&info->port, CharNStat & 0xff,
					flag);
			ToRecv--;
		}

		/*
		 * after we've emptied the FIFO in status mode, turn
		 * status mode back off
		 */
		if (sGetRxCnt(cp) == 0) {
#ifdef ROCKET_DEBUG_RECEIVE
			printk(KERN_INFO "Status mode off.\n");
#endif
			sDisRxStatusMode(cp);
		}
	} else {
		/*
		 * we aren't in status mode, so read down the FIFO two
		 * characters at time by doing repeated word IO
		 * transfer.
		 */
		space = tty_prepare_flip_string(&info->port, &cbuf, ToRecv);
		if (space < ToRecv) {
#ifdef ROCKET_DEBUG_RECEIVE
			printk(KERN_INFO "rp_do_receive:insufficient space ToRecv=%d space=%d\n", ToRecv, space);
#endif
			if (space <= 0)
				return;
			ToRecv = space;
		}
		wRecv = ToRecv >> 1;
		if (wRecv)
			sInStrW(sGetTxRxDataIO(cp), (unsigned short *) cbuf, wRecv);
		if (ToRecv & 1)
			cbuf[ToRecv - 1] = sInB(sGetTxRxDataIO(cp));
	}
	/*  Push the data up to the tty layer */
	tty_flip_buffer_push(&info->port);
}