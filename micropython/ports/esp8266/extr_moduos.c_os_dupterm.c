#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const mp_obj_t ;
struct TYPE_3__ {int /*<<< orphan*/  const (* var ) (size_t,int /*<<< orphan*/  const*) ;} ;
struct TYPE_4__ {TYPE_1__ fun; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mp_obj_get_type (int /*<<< orphan*/  const) ; 
 TYPE_2__ mp_uos_dupterm_obj ; 
 int /*<<< orphan*/  pyb_uart_type ; 
 int /*<<< orphan*/  const stub1 (size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  uart_attached_to_dupterm ; 

mp_obj_t os_dupterm(size_t n_args, const mp_obj_t *args) {
    mp_obj_t prev_obj = mp_uos_dupterm_obj.fun.var(n_args, args);
    if (mp_obj_get_type(args[0]) == &pyb_uart_type) {
        ++uart_attached_to_dupterm;
    }
    if (mp_obj_get_type(prev_obj) == &pyb_uart_type) {
        --uart_attached_to_dupterm;
    }
    return prev_obj;
}