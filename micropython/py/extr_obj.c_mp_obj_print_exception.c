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
typedef  size_t qstr ;
typedef  int /*<<< orphan*/  mp_print_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 size_t MP_QSTRnull ; 
 int /*<<< orphan*/  PRINT_EXC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_obj_exception_get_traceback (int /*<<< orphan*/ ,size_t*,size_t**) ; 
 scalar_t__ mp_obj_is_exception_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_print_helper (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_print_str (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  mp_printf (int /*<<< orphan*/  const*,char*,size_t,...) ; 

void mp_obj_print_exception(const mp_print_t *print, mp_obj_t exc) {
    if (mp_obj_is_exception_instance(exc)) {
        size_t n, *values;
        mp_obj_exception_get_traceback(exc, &n, &values);
        if (n > 0) {
            assert(n % 3 == 0);
            mp_print_str(print, "Traceback (most recent call last):\n");
            for (int i = n - 3; i >= 0; i -= 3) {
#if MICROPY_ENABLE_SOURCE_LINE
                mp_printf(print, "  File \"%q\", line %d", values[i], (int)values[i + 1]);
#else
                mp_printf(print, "  File \"%q\"", values[i]);
#endif
                // the block name can be NULL if it's unknown
                qstr block = values[i + 2];
                if (block == MP_QSTRnull) {
                    mp_print_str(print, "\n");
                } else {
                    mp_printf(print, ", in %q\n", block);
                }
            }
        }
    }
    mp_obj_print_helper(print, exc, PRINT_EXC);
    mp_print_str(print, "\n");
}