#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* value; } ;
struct TYPE_6__ {char const* value; } ;
typedef  TYPE_2__ CGI_varlist ;

/* Variables and functions */
 TYPE_2__* findvar (TYPE_2__*,char const*) ; 

const char *
CGI_lookup(CGI_varlist *v, const char *varname) {
    return (v = findvar(v, varname)) == 0 ? 0 : v->value->value;
}