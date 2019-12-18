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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int UART_BUFSIZE ; 
 int i_get ; 
 int i_put ; 
 int /*<<< orphan*/  k_sem_give (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  k_yield () ; 
 scalar_t__ mp_interrupt_char ; 
 int /*<<< orphan*/  mp_keyboard_interrupt () ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__* uart_ringbuf ; 
 int /*<<< orphan*/  uart_sem ; 

__attribute__((used)) static int console_irq_input_hook(uint8_t ch)
{
    int i_next = (i_put + 1) & (UART_BUFSIZE - 1);
    if (i_next == i_get) {
        printk("UART buffer overflow - char dropped\n");
        return 1;
    }
    if (ch == mp_interrupt_char) {
        mp_keyboard_interrupt();
        return 1;
    } else {
        uart_ringbuf[i_put] = ch;
        i_put = i_next;
    }
    //printk("%x\n", ch);
    k_sem_give(&uart_sem);
    k_yield();
    return 1;
}