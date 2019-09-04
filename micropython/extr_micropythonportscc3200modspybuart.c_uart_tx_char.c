#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  baudrate; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_UARTCharPutNonBlocking (int /*<<< orphan*/ ,int) ; 
 int PYBUART_TX_MAX_TIMEOUT_MS ; 
 int PYBUART_TX_WAIT_US (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTILS_DELAY_US_TO_COUNT (int) ; 
 int /*<<< orphan*/  UtilsDelay (int /*<<< orphan*/ ) ; 

bool uart_tx_char(pyb_uart_obj_t *self, int c) {
    uint32_t timeout = 0;
    while (!MAP_UARTCharPutNonBlocking(self->reg, c)) {
        if (timeout++ > ((PYBUART_TX_MAX_TIMEOUT_MS * 1000) / PYBUART_TX_WAIT_US(self->baudrate))) {
            return false;
        }
        UtilsDelay(UTILS_DELAY_US_TO_COUNT(PYBUART_TX_WAIT_US(self->baudrate)));
    }
    return true;
}