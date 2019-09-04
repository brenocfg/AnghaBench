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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  K_FOREVER ; 
 int UART_BUFSIZE ; 
 int i_get ; 
 unsigned int irq_lock () ; 
 int /*<<< orphan*/  irq_unlock (unsigned int) ; 
 int /*<<< orphan*/  k_sem_take (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uart_ringbuf ; 
 int /*<<< orphan*/  uart_sem ; 

uint8_t zephyr_getchar(void) {
    k_sem_take(&uart_sem, K_FOREVER);
    unsigned int key = irq_lock();
    uint8_t c = uart_ringbuf[i_get++];
    i_get &= UART_BUFSIZE - 1;
    irq_unlock(key);
    return c;
}