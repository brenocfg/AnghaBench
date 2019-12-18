#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  avl ;
struct TYPE_17__ {scalar_t__ hash_chart; int /*<<< orphan*/  foreachcounter; int /*<<< orphan*/  name; int /*<<< orphan*/  chart; int /*<<< orphan*/  spdim; struct TYPE_17__* next; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_15__ {int /*<<< orphan*/  alarms_idx_health_log; TYPE_4__* alarms_with_foreach; } ;
struct TYPE_14__ {scalar_t__ hash_name; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDHOST ;
typedef  TYPE_3__ RRDDIM ;
typedef  TYPE_4__ RRDCALC ;

/* Variables and functions */
 char* alarm_name_with_dim (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ avl_insert_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  freez (char*) ; 
 int /*<<< orphan*/  rrdcalc_add_to_host (TYPE_2__*,TYPE_4__*) ; 
 TYPE_4__* rrdcalc_create_from_rrdcalc (TYPE_4__*,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rrdcalc_exists (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ simple_pattern_matches (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void rrdcalc_link_to_rrddim(RRDDIM *rd, RRDSET *st, RRDHOST *host) {
    RRDCALC *rrdc;
    for (rrdc = host->alarms_with_foreach; rrdc ; rrdc = rrdc->next) {
        if (simple_pattern_matches(rrdc->spdim, rd->id) || simple_pattern_matches(rrdc->spdim, rd->name)) {
            if (rrdc->hash_chart == st->hash_name || !strcmp(rrdc->chart, st->name) || !strcmp(rrdc->chart, st->id)) {
                char *usename = alarm_name_with_dim(rrdc->name, strlen(rrdc->name), rd->name, strlen(rd->name));
                if (usename) {
                    if(rrdcalc_exists(host, st->name, usename, 0, 0)){
                        freez(usename);
                        continue;
                    }

                    RRDCALC *child = rrdcalc_create_from_rrdcalc(rrdc, host, usename, rd->name);
                    if (child) {
                        rrdcalc_add_to_host(host, child);
                        RRDCALC *rdcmp  = (RRDCALC *) avl_insert_lock(&(host)->alarms_idx_health_log,(avl *)child);
                        if (rdcmp != child) {
                            error("Cannot insert the alarm index ID %s",child->name);
                        }
                    } else {
                        error("Cannot allocate a new alarm.");
                        rrdc->foreachcounter--;
                    }
                }
            }
        }
    }
}