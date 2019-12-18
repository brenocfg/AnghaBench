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
struct TYPE_3__ {int attached_to_repl; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;

/* Variables and functions */

void uart_attach_to_repl(pyb_uart_obj_t *self, bool attached) {
    self->attached_to_repl = attached;
}