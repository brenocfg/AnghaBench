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
 int /*<<< orphan*/  pl011_uart_init () ; 
 char pl011_uart_recv () ; 
 int /*<<< orphan*/  pl011_uart_send (char) ; 
 int /*<<< orphan*/  pl011_uart_send_string (char*) ; 
 unsigned int semaphore ; 

void kernel_main(unsigned int proc_id)
{
    if (proc_id == 0)
    {
        pl011_uart_init();
    }

    while (semaphore != proc_id)
    {
        ;
    }

    // semaphore = 1;
    pl011_uart_send_string("Hello, world from processor ");
    pl011_uart_send((char)(proc_id + '0'));
    pl011_uart_send_string("\r\n");
    semaphore++;

    if (proc_id == 0)
    {
        while (1)
        {
            pl011_uart_send(pl011_uart_recv());
        }
    }
}