#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* variables; int /*<<< orphan*/  name; int /*<<< orphan*/  id; TYPE_1__* rrdset; } ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDDIMVAR ;
typedef  TYPE_3__ RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  D_VARIABLES ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddimvar_create_variables (TYPE_2__*) ; 

void rrddimvar_rename_all(RRDDIM *rd) {
    RRDSET *st = rd->rrdset;
    (void)st;

    debug(D_VARIABLES, "RRDDIMSET rename for chart id '%s' name '%s', dimension id '%s', name '%s'", st->id, st->name, rd->id, rd->name);

    RRDDIMVAR *rs, *next = rd->variables;
    while((rs = next)) {
        next = rs->next;
        rrddimvar_create_variables(rs);
    }
}