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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  console_command (int) ; 
 int /*<<< orphan*/  iwrap_buf_add (int) ; 
 int /*<<< orphan*/  iwrap_buf_del () ; 
 int /*<<< orphan*/  iwrap_buf_send () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  uart_available () ; 
 int uart_getchar () ; 
 int /*<<< orphan*/  uart_putchar (char) ; 

__attribute__((used)) static bool console(void) {
    // Send to Bluetoot module WT12
    static bool breaked = false;
    if (!uart_available())
        return false;
    else {
        uint8_t c;
        c = uart_getchar();
        uart_putchar(c);
        switch (c) {
            case 0x00:  // BREAK signal
                if (!breaked) {
                    print("break(? for help): ");
                    breaked = true;
                }
                break;
            case '\r':
                uart_putchar('\n');
                iwrap_buf_send();
                break;
            case '\b':
                iwrap_buf_del();
                break;
            default:
                if (breaked) {
                    print("\n");
                    console_command(c);
                    breaked = false;
                } else {
                    iwrap_buf_add(c);
                }
                break;
        }
        return true;
    }
}