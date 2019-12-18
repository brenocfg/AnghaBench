#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int uxbrg; int uxmode; int uxsta; } ;

/* Variables and functions */
 TYPE_1__ UART1 ; 

void uart_init(void) {
    // baudrate = F_CY / 16 (uxbrg + 1)
    // F_CY = 40MHz for us
    UART1.uxbrg = 64; // 38400 baud
    UART1.uxmode = 1 << 15; // UARTEN
    UART1.uxsta = 1 << 10;  // UTXEN
}