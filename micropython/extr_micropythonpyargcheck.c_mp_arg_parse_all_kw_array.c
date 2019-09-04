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
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_map_t ;
typedef  int /*<<< orphan*/  mp_arg_val_t ;
typedef  int /*<<< orphan*/  mp_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_arg_parse_all (size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_map_init_fixed_table (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 

void mp_arg_parse_all_kw_array(size_t n_pos, size_t n_kw, const mp_obj_t *args, size_t n_allowed, const mp_arg_t *allowed, mp_arg_val_t *out_vals) {
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_pos);
    mp_arg_parse_all(n_pos, args, &kw_args, n_allowed, allowed, out_vals);
}