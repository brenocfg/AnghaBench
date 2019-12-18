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
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* print_strn ) (int /*<<< orphan*/ ,char const*,size_t) ;} ;
typedef  TYPE_1__ mp_print_t ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,size_t) ; 

int mp_print_str(const mp_print_t *print, const char *str) {
    size_t len = strlen(str);
    if (len) {
        print->print_strn(print->data, str, len);
    }
    return len;
}