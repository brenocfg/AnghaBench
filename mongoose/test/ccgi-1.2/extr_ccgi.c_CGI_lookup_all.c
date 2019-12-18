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
struct TYPE_7__ {char* value; struct TYPE_7__* next; } ;
struct TYPE_6__ {scalar_t__ vector; int numvalue; TYPE_2__* value; } ;
typedef  TYPE_1__ CGI_varlist ;
typedef  int /*<<< orphan*/  CGI_value ;
typedef  TYPE_2__ CGI_val ;

/* Variables and functions */
 TYPE_1__* findvar (TYPE_1__*,char const*) ; 
 scalar_t__ mymalloc (int) ; 

CGI_value *
CGI_lookup_all(CGI_varlist *v, const char *varname) {
    CGI_val *val;
    int i;

    if ((v = findvar(v, varname)) == 0) {
        return 0;
    }
    if (v->vector == 0) {
        v->vector = (CGI_value *)
            mymalloc(sizeof(CGI_value) * (v->numvalue + 1));
        i = 0;

        /* to initialize v->vector we must cast away const */

        for (val = v->value; val != 0 && i < v->numvalue;
            val = val->next)
        {
            ((const char **)v->vector)[i++] = val->value;
        }
        ((const char **)v->vector)[i] = 0;
    }
    return v->vector;
}