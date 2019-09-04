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
struct TYPE_8__ {char* id; TYPE_1__* variables; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int options; struct TYPE_7__* value; struct TYPE_7__* variable; struct TYPE_7__* next; int /*<<< orphan*/  key_fullname; TYPE_2__* rrdset; } ;
typedef  TYPE_1__ RRDSETVAR ;
typedef  TYPE_2__ RRDSET ;

/* Variables and functions */
 int /*<<< orphan*/  D_VARIABLES ; 
 int RRDVAR_OPTION_ALLOCATED ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdsetvar_free_variables (TYPE_1__*) ; 

void rrdsetvar_free(RRDSETVAR *rs) {
    RRDSET *st = rs->rrdset;
    debug(D_VARIABLES, "RRDSETVAR free for chart id '%s' name '%s', variable '%s'", st->id, st->name, rs->variable);

    if(st->variables == rs) {
        st->variables = rs->next;
    }
    else {
        RRDSETVAR *t;
        for (t = st->variables; t && t->next != rs; t = t->next);
        if(!t) error("RRDSETVAR '%s' not found in chart '%s' variables linked list", rs->key_fullname, st->id);
        else t->next = rs->next;
    }

    rrdsetvar_free_variables(rs);

    freez(rs->variable);

    if(rs->options & RRDVAR_OPTION_ALLOCATED)
        freez(rs->value);

    freez(rs);
}