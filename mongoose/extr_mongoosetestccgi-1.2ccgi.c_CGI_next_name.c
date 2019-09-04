#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* iter; } ;
struct TYPE_4__ {char const* varname; struct TYPE_4__* next; } ;
typedef  TYPE_2__ CGI_varlist ;

/* Variables and functions */

const char *
CGI_next_name(CGI_varlist *v) {
    return v == 0 || v->iter == 0 || (v->iter = v->iter->next) == 0 ?
        0 : v->iter->varname;
}