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
typedef  int /*<<< orphan*/  pin_obj_t ;
typedef  int /*<<< orphan*/  mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MP_OBJ_FUN_ARGS_MAX ; 
 int /*<<< orphan*/  mp_arg_check_num (size_t,size_t,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_map_init_fixed_table (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * pin_find (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pin_obj_init_helper (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

mp_obj_t mp_pin_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);

    // Run an argument through the mapper and return the result.
    const pin_obj_t *pin = pin_find(args[0]);

    if (n_args > 1 || n_kw > 0) {
        // pin mode given, so configure this GPIO
        mp_map_t kw_args;
        mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
        pin_obj_init_helper(pin, n_args - 1, args + 1, &kw_args);
    }

    return MP_OBJ_FROM_PTR(pin);
}