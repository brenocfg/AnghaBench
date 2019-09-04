#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int stop_bits; int data_bits; scalar_t__ parity; int data_rate; scalar_t__ loopback; } ;
struct TYPE_13__ {int port_num; int serial_signals; unsigned char ie0_value; unsigned char ie1_value; unsigned char ie2_value; TYPE_2__ params; TYPE_1__** port_array; } ;
struct TYPE_11__ {unsigned char ctrlreg_value; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ ASYNC_PARITY_NONE ; 
 scalar_t__ ASYNC_PARITY_ODD ; 
 unsigned char BIT0 ; 
 unsigned char BIT1 ; 
 unsigned char BIT2 ; 
 unsigned char BIT3 ; 
 unsigned char BIT4 ; 
 unsigned char BIT5 ; 
 unsigned char BIT6 ; 
 unsigned char BRKD ; 
 int /*<<< orphan*/  CTL ; 
 int /*<<< orphan*/  IE0 ; 
 int /*<<< orphan*/  IE1 ; 
 int /*<<< orphan*/  IE2 ; 
 int /*<<< orphan*/  MD0 ; 
 int /*<<< orphan*/  MD1 ; 
 int /*<<< orphan*/  MD2 ; 
 unsigned char OVRN ; 
 int /*<<< orphan*/  RRC ; 
 unsigned char RXINTE ; 
 int /*<<< orphan*/  RXS ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  TRC0 ; 
 int /*<<< orphan*/  TRC1 ; 
 unsigned char TXINTE ; 
 int /*<<< orphan*/  TXS ; 
 int /*<<< orphan*/  rx_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  set_rate (TYPE_3__*,int) ; 
 int /*<<< orphan*/  tx_set_idle (TYPE_3__*) ; 
 int /*<<< orphan*/  tx_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  write_control_reg (TYPE_3__*) ; 
 int /*<<< orphan*/  write_reg (TYPE_3__*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void async_mode(SLMP_INFO *info)
{

  	unsigned char RegValue;

	tx_stop(info);
	rx_stop(info);

	/* MD0, Mode Register 0
	 *
	 * 07..05  PRCTL<2..0>, Protocol Mode, 000=async
	 * 04      AUTO, Auto-enable (RTS/CTS/DCD)
	 * 03      Reserved, must be 0
	 * 02      CRCCC, CRC Calculation, 0=disabled
	 * 01..00  STOP<1..0> Stop bits (00=1,10=2)
	 *
	 * 0000 0000
	 */
	RegValue = 0x00;
	if (info->params.stop_bits != 1)
		RegValue |= BIT1;
	write_reg(info, MD0, RegValue);

	/* MD1, Mode Register 1
	 *
	 * 07..06  BRATE<1..0>, bit rate, 00=1/1 01=1/16 10=1/32 11=1/64
	 * 05..04  TXCHR<1..0>, tx char size, 00=8 bits,01=7,10=6,11=5
	 * 03..02  RXCHR<1..0>, rx char size
	 * 01..00  PMPM<1..0>, Parity mode, 00=none 10=even 11=odd
	 *
	 * 0100 0000
	 */
	RegValue = 0x40;
	switch (info->params.data_bits) {
	case 7: RegValue |= BIT4 + BIT2; break;
	case 6: RegValue |= BIT5 + BIT3; break;
	case 5: RegValue |= BIT5 + BIT4 + BIT3 + BIT2; break;
	}
	if (info->params.parity != ASYNC_PARITY_NONE) {
		RegValue |= BIT1;
		if (info->params.parity == ASYNC_PARITY_ODD)
			RegValue |= BIT0;
	}
	write_reg(info, MD1, RegValue);

	/* MD2, Mode Register 2
	 *
	 * 07..02  Reserved, must be 0
	 * 01..00  CNCT<1..0> Channel connection, 00=normal 11=local loopback
	 *
	 * 0000 0000
	 */
	RegValue = 0x00;
	if (info->params.loopback)
		RegValue |= (BIT1 + BIT0);
	write_reg(info, MD2, RegValue);

	/* RXS, Receive clock source
	 *
	 * 07      Reserved, must be 0
	 * 06..04  RXCS<2..0>, clock source, 000=RxC Pin, 100=BRG, 110=DPLL
	 * 03..00  RXBR<3..0>, rate divisor, 0000=1
	 */
	RegValue=BIT6;
	write_reg(info, RXS, RegValue);

	/* TXS, Transmit clock source
	 *
	 * 07      Reserved, must be 0
	 * 06..04  RXCS<2..0>, clock source, 000=TxC Pin, 100=BRG, 110=Receive Clock
	 * 03..00  RXBR<3..0>, rate divisor, 0000=1
	 */
	RegValue=BIT6;
	write_reg(info, TXS, RegValue);

	/* Control Register
	 *
	 * 6,4,2,0  CLKSEL<3..0>, 0 = TcCLK in, 1 = Auxclk out
	 */
	info->port_array[0]->ctrlreg_value |= (BIT0 << (info->port_num * 2));
	write_control_reg(info);

	tx_set_idle(info);

	/* RRC Receive Ready Control 0
	 *
	 * 07..05  Reserved, must be 0
	 * 04..00  RRC<4..0> Rx FIFO trigger active 0x00 = 1 byte
	 */
	write_reg(info, RRC, 0x00);

	/* TRC0 Transmit Ready Control 0
	 *
	 * 07..05  Reserved, must be 0
	 * 04..00  TRC<4..0> Tx FIFO trigger active 0x10 = 16 bytes
	 */
	write_reg(info, TRC0, 0x10);

	/* TRC1 Transmit Ready Control 1
	 *
	 * 07..05  Reserved, must be 0
	 * 04..00  TRC<4..0> Tx FIFO trigger inactive 0x1e = 31 bytes (full-1)
	 */
	write_reg(info, TRC1, 0x1e);

	/* CTL, MSCI control register
	 *
	 * 07..06  Reserved, set to 0
	 * 05      UDRNC, underrun control, 0=abort 1=CRC+flag (HDLC/BSC)
	 * 04      IDLC, idle control, 0=mark 1=idle register
	 * 03      BRK, break, 0=off 1 =on (async)
	 * 02      SYNCLD, sync char load enable (BSC) 1=enabled
	 * 01      GOP, go active on poll (LOOP mode) 1=enabled
	 * 00      RTS, RTS output control, 0=active 1=inactive
	 *
	 * 0001 0001
	 */
	RegValue = 0x10;
	if (!(info->serial_signals & SerialSignal_RTS))
		RegValue |= 0x01;
	write_reg(info, CTL, RegValue);

	/* enable status interrupts */
	info->ie0_value |= TXINTE + RXINTE;
	write_reg(info, IE0, info->ie0_value);

	/* enable break detect interrupt */
	info->ie1_value = BRKD;
	write_reg(info, IE1, info->ie1_value);

	/* enable rx overrun interrupt */
	info->ie2_value = OVRN;
	write_reg(info, IE2, info->ie2_value);

	set_rate( info, info->params.data_rate * 16 );
}