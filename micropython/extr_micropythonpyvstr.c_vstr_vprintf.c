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
typedef  int /*<<< orphan*/  vstr_t ;
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ mp_print_t ;
typedef  int /*<<< orphan*/  mp_print_strn_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_vprintf (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vstr_add_strn ; 

void vstr_vprintf(vstr_t *vstr, const char *fmt, va_list ap) {
    mp_print_t print = {vstr, (mp_print_strn_t)vstr_add_strn};
    mp_vprintf(&print, fmt, ap);
}