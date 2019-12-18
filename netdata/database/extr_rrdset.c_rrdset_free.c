#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {char* hostname; TYPE_1__* rrdset_root; } ;
struct TYPE_17__ {int rrd_memory_mode; int /*<<< orphan*/  memsize; int /*<<< orphan*/  name; struct TYPE_17__* module_name; struct TYPE_17__* plugin_name; struct TYPE_17__* config_section; int /*<<< orphan*/  rrdset_rwlock; int /*<<< orphan*/  id; struct TYPE_17__* next; int /*<<< orphan*/  rrdvar_root_index; int /*<<< orphan*/  rrdfamily; scalar_t__ dimensions; scalar_t__ alarms; scalar_t__ variables; TYPE_2__* rrdhost; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  D_RRD_CALLS ; 
#define  RRD_MEMORY_MODE_ALLOC 133 
#define  RRD_MEMORY_MODE_DBENGINE 132 
#define  RRD_MEMORY_MODE_MAP 131 
#define  RRD_MEMORY_MODE_NONE 130 
#define  RRD_MEMORY_MODE_RAM 129 
#define  RRD_MEMORY_MODE_SAVE 128 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 int /*<<< orphan*/  munmap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdata_rwlock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrddim_free (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  rrdfamily_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdhost_check_wrlock (TYPE_2__*) ; 
 TYPE_1__* rrdset_index_del (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  rrdset_index_del_name (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  rrdset_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdset_wrlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdsetcalc_unlink (scalar_t__) ; 
 int /*<<< orphan*/  rrdsetvar_free (scalar_t__) ; 
 int /*<<< orphan*/  rrdvar_free_remaining_variables (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void rrdset_free(RRDSET *st) {
    if(unlikely(!st)) return;

    RRDHOST *host = st->rrdhost;

    rrdhost_check_wrlock(host);  // make sure we have a write lock on the host
    rrdset_wrlock(st);                  // lock this RRDSET

    // info("Removing chart '%s' ('%s')", st->id, st->name);

    // ------------------------------------------------------------------------
    // remove it from the indexes

    if(unlikely(rrdset_index_del(host, st) != st))
        error("RRDSET: INTERNAL ERROR: attempt to remove from index chart '%s', removed a different chart.", st->id);

    rrdset_index_del_name(host, st);

    // ------------------------------------------------------------------------
    // free its children structures

    while(st->variables)  rrdsetvar_free(st->variables);
    while(st->alarms)     rrdsetcalc_unlink(st->alarms);
    while(st->dimensions) rrddim_free(st, st->dimensions);

    rrdfamily_free(host, st->rrdfamily);

    debug(D_RRD_CALLS, "RRDSET: Cleaning up remaining chart variables for host '%s', chart '%s'", host->hostname, st->id);
    rrdvar_free_remaining_variables(host, &st->rrdvar_root_index);

    // ------------------------------------------------------------------------
    // unlink it from the host

    if(st == host->rrdset_root) {
        host->rrdset_root = st->next;
    }
    else {
        // find the previous one
        RRDSET *s;
        for(s = host->rrdset_root; s && s->next != st ; s = s->next) ;

        // bypass it
        if(s) s->next = st->next;
        else error("Request to free RRDSET '%s': cannot find it under host '%s'", st->id, host->hostname);
    }

    rrdset_unlock(st);

    // ------------------------------------------------------------------------
    // free it

    netdata_rwlock_destroy(&st->rrdset_rwlock);

    // free directly allocated members
    freez(st->config_section);
    freez(st->plugin_name);
    freez(st->module_name);

    switch(st->rrd_memory_mode) {
        case RRD_MEMORY_MODE_SAVE:
        case RRD_MEMORY_MODE_MAP:
        case RRD_MEMORY_MODE_RAM:
            debug(D_RRD_CALLS, "Unmapping stats '%s'.", st->name);
            munmap(st, st->memsize);
            break;

        case RRD_MEMORY_MODE_ALLOC:
        case RRD_MEMORY_MODE_NONE:
        case RRD_MEMORY_MODE_DBENGINE:
            freez(st);
            break;
    }
}