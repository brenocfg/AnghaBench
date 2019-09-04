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
typedef  int __u8 ;

/* Variables and functions */
 int LSR_BREAK ; 
 int LSR_FRM_ERR ; 
 int LSR_OVER_ERR ; 
 int LSR_PAR_ERR ; 
 int LSR_RX_AVAIL ; 
 int LSR_TX_EMPTY ; 
 int UMP_UART_LSR_BR_MASK ; 
 int UMP_UART_LSR_FE_MASK ; 
 int UMP_UART_LSR_OV_MASK ; 
 int UMP_UART_LSR_PE_MASK ; 
 int UMP_UART_LSR_RX_MASK ; 
 int UMP_UART_LSR_TX_MASK ; 

__attribute__((used)) static __u8 map_line_status(__u8 ti_lsr)
{
	__u8 lsr = 0;

#define MAP_FLAG(flagUmp, flagUart)    \
	if (ti_lsr & flagUmp) \
		lsr |= flagUart;

	MAP_FLAG(UMP_UART_LSR_OV_MASK, LSR_OVER_ERR)	/* overrun */
	MAP_FLAG(UMP_UART_LSR_PE_MASK, LSR_PAR_ERR)	/* parity error */
	MAP_FLAG(UMP_UART_LSR_FE_MASK, LSR_FRM_ERR)	/* framing error */
	MAP_FLAG(UMP_UART_LSR_BR_MASK, LSR_BREAK)	/* break detected */
	MAP_FLAG(UMP_UART_LSR_RX_MASK, LSR_RX_AVAIL)	/* rx data available */
	MAP_FLAG(UMP_UART_LSR_TX_MASK, LSR_TX_EMPTY)	/* tx hold reg empty */

#undef MAP_FLAG

	return lsr;
}