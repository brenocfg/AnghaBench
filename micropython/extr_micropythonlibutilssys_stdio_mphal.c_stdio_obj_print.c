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
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ sys_stdio_obj_t ;
typedef  int /*<<< orphan*/  mp_print_t ;
typedef  int /*<<< orphan*/  mp_print_kind_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_printf (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 

void stdio_obj_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    sys_stdio_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "<io.FileIO %d>", self->fd);
}