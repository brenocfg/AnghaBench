#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; scalar_t__ value; } ;
struct TYPE_7__ {int numvalue; scalar_t__ vector; struct TYPE_7__* iter; TYPE_2__* valtail; struct TYPE_7__* tail; struct TYPE_7__* next; TYPE_2__* value; scalar_t__ varname; } ;
typedef  TYPE_1__ CGI_varlist ;
typedef  TYPE_2__ CGI_val ;

/* Variables and functions */
 TYPE_1__* findvar (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ mymalloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

CGI_varlist *
CGI_add_var(CGI_varlist *v, const char *varname, const char *value) {
    CGI_val     *val;
    CGI_varlist *v2;

    if (varname == 0 || value == 0) {
        return v;
    }

    /* create a new value */

    val = (CGI_val *) mymalloc(sizeof(*val) + strlen(value));
    strcpy((char *) val->value, value);
    val->next = 0;

    /*
     * find the list entry or else create a new one.  Add the
     * new value.  We use "tail" pointers to keep the lists
     * in the same order as the input.
     */

    if ((v2 = findvar(v, varname)) == 0) {
        v2 = (CGI_varlist *) mymalloc(sizeof(*v2) + strlen(varname));
        strcpy((char *) v2->varname, varname);
        v2->value = val;
        v2->numvalue = 1;
        v2->next = v2->iter = v2->tail = 0;
        v2->vector = 0;
        if (v == 0) {
            v = v2;
        }
        else {
            v->tail->next = v2;
        }
        v->tail = v2;
    }
    else {
        v2->valtail->next = val;
        v2->numvalue++;
    }
    v2->valtail = val;
    if (v2->vector != 0) {
        free((void *)v2->vector);
        v2->vector = 0;
    }
    v->iter = 0;
    return v;
}