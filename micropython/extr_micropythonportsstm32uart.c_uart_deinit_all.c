#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  is_static; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;

/* Variables and functions */
 int MP_ARRAY_SIZE (TYPE_1__**) ; 
 TYPE_1__** MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_uart_obj_all ; 
 int /*<<< orphan*/  uart_deinit (TYPE_1__*) ; 

void uart_deinit_all(void) {
    for (int i = 0; i < MP_ARRAY_SIZE(MP_STATE_PORT(pyb_uart_obj_all)); i++) {
        pyb_uart_obj_t *uart_obj = MP_STATE_PORT(pyb_uart_obj_all)[i];
        if (uart_obj != NULL && !uart_obj->is_static) {
            uart_deinit(uart_obj);
            MP_STATE_PORT(pyb_uart_obj_all)[i] = NULL;
        }
    }
}