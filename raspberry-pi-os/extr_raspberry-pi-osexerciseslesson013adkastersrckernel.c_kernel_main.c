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

/* Variables and functions */
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  uart_init () ; 
 int /*<<< orphan*/  uart_recv () ; 
 int /*<<< orphan*/  uart_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_send_string (char*) ; 

void kernel_main(int procid)
{
	char procstr[2];
	procstr[0] = procid + '0';
	procstr[1] = 0;

	if(procid == 0) {
		uart_init();
	}
    else
	{
		delay(100000 * procid);
	}

	uart_send_string("Hello from processor ");
	uart_send_string(procstr);
	uart_send_string("\r\n");

    // Don't spin this with every processor or we'll have issues D:
    if(procid ==0) {
		while (1) {
			uart_send(uart_recv());
		}
	}
	else {
		while(1) {}
	}
}