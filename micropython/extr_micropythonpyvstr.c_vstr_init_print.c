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
struct TYPE_3__ {scalar_t__ print_strn; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ mp_print_t ;
typedef  scalar_t__ mp_print_strn_t ;

/* Variables and functions */
 scalar_t__ vstr_add_strn ; 
 int /*<<< orphan*/  vstr_init (int /*<<< orphan*/ *,size_t) ; 

void vstr_init_print(vstr_t *vstr, size_t alloc, mp_print_t *print) {
    vstr_init(vstr, alloc);
    print->data = vstr;
    print->print_strn = (mp_print_strn_t)vstr_add_strn;
}