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

/* Variables and functions */
 int /*<<< orphan*/  mp_call_function_n_kw (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

mp_obj_t mp_call_function_2(mp_obj_t fun, mp_obj_t arg1, mp_obj_t arg2) {
    mp_obj_t args[2];
    args[0] = arg1;
    args[1] = arg2;
    return mp_call_function_n_kw(fun, 2, 0, args);
}