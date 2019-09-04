#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* families; struct TYPE_9__* hosts; struct TYPE_9__* contexts; struct TYPE_9__* charts; struct TYPE_9__* alarms; int /*<<< orphan*/  families_pattern; int /*<<< orphan*/  hosts_pattern; int /*<<< orphan*/  contexts_pattern; int /*<<< orphan*/  charts_pattern; int /*<<< orphan*/  alarms_pattern; struct TYPE_9__* next; } ;
typedef  TYPE_1__ SILENCER ;

/* Variables and functions */
 int /*<<< orphan*/  D_HEALTH ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 int /*<<< orphan*/  simple_pattern_free (int /*<<< orphan*/ ) ; 

void free_silencers(SILENCER *t) {
    if (!t) return;
    if (t->next) free_silencers(t->next);
    debug(D_HEALTH, "HEALTH command API: Freeing silencer %s:%s:%s:%s:%s", t->alarms,
          t->charts, t->contexts, t->hosts, t->families);
    simple_pattern_free(t->alarms_pattern);
    simple_pattern_free(t->charts_pattern);
    simple_pattern_free(t->contexts_pattern);
    simple_pattern_free(t->hosts_pattern);
    simple_pattern_free(t->families_pattern);
    freez(t->alarms);
    freez(t->charts);
    freez(t->contexts);
    freez(t->hosts);
    freez(t->families);
    freez(t);
    return;
}