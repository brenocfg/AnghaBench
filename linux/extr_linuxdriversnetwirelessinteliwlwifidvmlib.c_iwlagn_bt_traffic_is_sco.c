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
struct iwl_bt_uart_msg {int frame3; } ;

/* Variables and functions */
 int BT_UART_MSG_FRAME3SCOESCO_MSK ; 
 int BT_UART_MSG_FRAME3SCOESCO_POS ; 

__attribute__((used)) static bool iwlagn_bt_traffic_is_sco(struct iwl_bt_uart_msg *uart_msg)
{
	return (BT_UART_MSG_FRAME3SCOESCO_MSK & uart_msg->frame3) >>
		BT_UART_MSG_FRAME3SCOESCO_POS;
}