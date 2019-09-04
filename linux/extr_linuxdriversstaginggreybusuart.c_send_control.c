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
typedef  int /*<<< orphan*/  u8 ;
struct gb_uart_set_control_line_state_request {int /*<<< orphan*/  control; } ;
struct gb_tty {int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_UART_TYPE_SET_CONTROL_LINE_STATE ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_uart_set_control_line_state_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_control(struct gb_tty *gb_tty, u8 control)
{
	struct gb_uart_set_control_line_state_request request;

	request.control = control;
	return gb_operation_sync(gb_tty->connection,
				 GB_UART_TYPE_SET_CONTROL_LINE_STATE,
				 &request, sizeof(request), NULL, 0);
}