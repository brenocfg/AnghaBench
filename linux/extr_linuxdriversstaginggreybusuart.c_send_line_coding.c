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
struct gb_uart_set_line_coding_request {int dummy; } ;
struct gb_tty {int /*<<< orphan*/  connection; int /*<<< orphan*/  line_coding; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_UART_TYPE_SET_LINE_CODING ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_uart_set_line_coding_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct gb_uart_set_line_coding_request*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int send_line_coding(struct gb_tty *tty)
{
	struct gb_uart_set_line_coding_request request;

	memcpy(&request, &tty->line_coding,
	       sizeof(tty->line_coding));
	return gb_operation_sync(tty->connection, GB_UART_TYPE_SET_LINE_CODING,
				 &request, sizeof(request), NULL, 0);
}