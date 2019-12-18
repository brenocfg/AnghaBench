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
 int is_uart_inited ; 
 int /*<<< orphan*/  uart_init (int) ; 
 int uart_recv () ; 
 int /*<<< orphan*/  uart_send (int) ; 
 int /*<<< orphan*/  uart_send_string (char*) ; 

void kernel_main(int corenum)
{
    if(0==corenum)
    {
        uart_init(115200);
        is_uart_inited = true;
        //output something to make sure only init uart once
        uart_send(corenum+'0');
        uart_send_string("\r\n");
    }
    while(!is_uart_inited);    //wait uart init OK
    delay(corenum*200000);     //I find the origin delay cannot use 0 as parameter, so I make some change to delay function 
    uart_send_string("Hello, world! From processor <");
    uart_send(corenum+'0');
    uart_send_string(">\r\n");

    if(0==corenum)
    {
        while (1) {
            uart_send(uart_recv());
        }

    }
    else
    {
        while(1);
    }
}