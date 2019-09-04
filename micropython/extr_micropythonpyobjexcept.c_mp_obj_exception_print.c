#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_print_t ;
typedef  scalar_t__ mp_print_kind_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_7__ {TYPE_1__* type; } ;
struct TYPE_8__ {TYPE_5__* args; TYPE_2__ base; } ;
typedef  TYPE_3__ mp_obj_exception_t ;
struct TYPE_9__ {int len; int /*<<< orphan*/ * items; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_5__*) ; 
 TYPE_3__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ PRINT_EXC ; 
 scalar_t__ PRINT_EXC_SUBCLASS ; 
 scalar_t__ PRINT_REPR ; 
 scalar_t__ PRINT_STR ; 
 int /*<<< orphan*/  mp_obj_print_helper (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_tuple_print (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mp_print_str (int /*<<< orphan*/  const*,char*) ; 
 char* qstr_str (int /*<<< orphan*/ ) ; 

void mp_obj_exception_print(const mp_print_t *print, mp_obj_t o_in, mp_print_kind_t kind) {
    mp_obj_exception_t *o = MP_OBJ_TO_PTR(o_in);
    mp_print_kind_t k = kind & ~PRINT_EXC_SUBCLASS;
    bool is_subclass = kind & PRINT_EXC_SUBCLASS;
    if (!is_subclass && (k == PRINT_REPR || k == PRINT_EXC)) {
        mp_print_str(print, qstr_str(o->base.type->name));
    }

    if (k == PRINT_EXC) {
        mp_print_str(print, ": ");
    }

    if (k == PRINT_STR || k == PRINT_EXC) {
        if (o->args == NULL || o->args->len == 0) {
            mp_print_str(print, "");
            return;
        } else if (o->args->len == 1) {
            #if MICROPY_PY_UERRNO
            // try to provide a nice OSError error message
            if (o->base.type == &mp_type_OSError && mp_obj_is_small_int(o->args->items[0])) {
                qstr qst = mp_errno_to_str(o->args->items[0]);
                if (qst != MP_QSTR_NULL) {
                    mp_printf(print, "[Errno " INT_FMT "] %q", MP_OBJ_SMALL_INT_VALUE(o->args->items[0]), qst);
                    return;
                }
            }
            #endif
            mp_obj_print_helper(print, o->args->items[0], PRINT_STR);
            return;
        }
    }
    mp_obj_tuple_print(print, MP_OBJ_FROM_PTR(o->args), kind);
}