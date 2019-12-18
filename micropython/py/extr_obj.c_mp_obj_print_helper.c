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
typedef  int /*<<< orphan*/  mp_print_t ;
typedef  int /*<<< orphan*/  mp_print_kind_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  (* print ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NULL ; 
 int /*<<< orphan*/  MP_STACK_CHECK () ; 
 TYPE_1__* mp_obj_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_print_str (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  mp_printf (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mp_obj_print_helper(const mp_print_t *print, mp_obj_t o_in, mp_print_kind_t kind) {
    // There can be data structures nested too deep, or just recursive
    MP_STACK_CHECK();
#ifndef NDEBUG
    if (o_in == MP_OBJ_NULL) {
        mp_print_str(print, "(nil)");
        return;
    }
#endif
    mp_obj_type_t *type = mp_obj_get_type(o_in);
    if (type->print != NULL) {
        type->print((mp_print_t*)print, o_in, kind);
    } else {
        mp_printf(print, "<%q>", type->name);
    }
}