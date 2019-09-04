#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct jsm_channel {int ch_mistat; int ch_mostat; int /*<<< orphan*/  ch_portnum; TYPE_1__* ch_bd; int /*<<< orphan*/  uart_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSIGS ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DDCD ; 
 int UART_MSR_DDSR ; 
 int UART_MSR_DSR ; 
 int UART_MSR_RI ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cls_parse_modem(struct jsm_channel *ch, u8 signals)
{
	u8 msignals = signals;

	jsm_dbg(MSIGS, &ch->ch_bd->pci_dev,
		"neo_parse_modem: port: %d msignals: %x\n",
		ch->ch_portnum, msignals);

	/*
	 * Scrub off lower bits.
	 * They signify delta's, which I don't care about
	 * Keep DDCD and DDSR though
	 */
	msignals &= 0xf8;

	if (msignals & UART_MSR_DDCD)
		uart_handle_dcd_change(&ch->uart_port, msignals & UART_MSR_DCD);
	if (msignals & UART_MSR_DDSR)
		uart_handle_dcd_change(&ch->uart_port, msignals & UART_MSR_CTS);

	if (msignals & UART_MSR_DCD)
		ch->ch_mistat |= UART_MSR_DCD;
	else
		ch->ch_mistat &= ~UART_MSR_DCD;

	if (msignals & UART_MSR_DSR)
		ch->ch_mistat |= UART_MSR_DSR;
	else
		ch->ch_mistat &= ~UART_MSR_DSR;

	if (msignals & UART_MSR_RI)
		ch->ch_mistat |= UART_MSR_RI;
	else
		ch->ch_mistat &= ~UART_MSR_RI;

	if (msignals & UART_MSR_CTS)
		ch->ch_mistat |= UART_MSR_CTS;
	else
		ch->ch_mistat &= ~UART_MSR_CTS;

	jsm_dbg(MSIGS, &ch->ch_bd->pci_dev,
		"Port: %d DTR: %d RTS: %d CTS: %d DSR: %d " "RI: %d CD: %d\n",
		ch->ch_portnum,
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MCR_DTR),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MCR_RTS),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MSR_CTS),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MSR_DSR),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MSR_RI),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MSR_DCD));
}