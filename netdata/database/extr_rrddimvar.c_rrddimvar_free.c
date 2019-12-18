#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  id; TYPE_2__* variables; int /*<<< orphan*/  name; TYPE_1__* rrdset; } ;
struct TYPE_8__ {struct TYPE_8__* suffix; struct TYPE_8__* prefix; struct TYPE_8__* next; int /*<<< orphan*/  key_name; TYPE_3__* rrddim; } ;
struct TYPE_7__ {char* id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDDIMVAR ;
typedef  TYPE_3__ RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  D_VARIABLES ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freez (TYPE_2__*) ; 
 int /*<<< orphan*/  rrddimvar_free_variables (TYPE_2__*) ; 

void rrddimvar_free(RRDDIMVAR *rs) {
    RRDDIM *rd = rs->rrddim;
    RRDSET *st = rd->rrdset;
    debug(D_VARIABLES, "RRDDIMSET free for chart id '%s' name '%s', dimension id '%s', name '%s', prefix='%s', suffix='%s'", st->id, st->name, rd->id, rd->name, rs->prefix, rs->suffix);

    rrddimvar_free_variables(rs);

    if(rd->variables == rs) {
        debug(D_VARIABLES, "RRDDIMSET removing first entry for chart id '%s' name '%s', dimension id '%s', name '%s'", st->id, st->name, rd->id, rd->name);
        rd->variables = rs->next;
    }
    else {
        debug(D_VARIABLES, "RRDDIMSET removing non-first entry for chart id '%s' name '%s', dimension id '%s', name '%s'", st->id, st->name, rd->id, rd->name);
        RRDDIMVAR *t;
        for (t = rd->variables; t && t->next != rs; t = t->next) ;
        if(!t) error("RRDDIMVAR '%s' not found in dimension '%s/%s' variables linked list", rs->key_name, st->id, rd->id);
        else t->next = rs->next;
    }

    freez(rs->prefix);
    freez(rs->suffix);
    freez(rs);
}