#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rrd_update_every; } ;
struct TYPE_3__ {int usages_count; int persons_count; int machines_count; int urls_count; int persons_urls_count; int machines_urls_count; int persons_memory; int machines_memory; int urls_memory; int persons_urls_memory; int machines_urls_memory; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  NAME_VALUE ;
typedef  int /*<<< orphan*/  DICTIONARY ;

/* Variables and functions */
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 TYPE_2__* localhost ; 
 TYPE_1__ registry ; 
 int /*<<< orphan*/  rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void registry_statistics(void) {
    if(!registry.enabled) return;

    static RRDSET *sts = NULL, *stc = NULL, *stm = NULL;

    if(unlikely(!sts)) {
        sts = rrdset_create_localhost(
                "netdata"
                , "registry_sessions"
                , NULL
                , "registry"
                , NULL
                , "NetData Registry Sessions"
                , "sessions"
                , "registry"
                , "stats"
                , 131000
                , localhost->rrd_update_every
                , RRDSET_TYPE_LINE
        );

        rrddim_add(sts, "sessions",  NULL,  1, 1, RRD_ALGORITHM_ABSOLUTE);
    }
    else rrdset_next(sts);

    rrddim_set(sts, "sessions", registry.usages_count);
    rrdset_done(sts);

    // ------------------------------------------------------------------------

    if(unlikely(!stc)) {
        stc = rrdset_create_localhost(
                "netdata"
                , "registry_entries"
                , NULL
                , "registry"
                , NULL
                , "NetData Registry Entries"
                , "entries"
                , "registry"
                , "stats"
                , 131100
                , localhost->rrd_update_every
                , RRDSET_TYPE_LINE
        );

        rrddim_add(stc, "persons",        NULL,  1, 1, RRD_ALGORITHM_ABSOLUTE);
        rrddim_add(stc, "machines",       NULL,  1, 1, RRD_ALGORITHM_ABSOLUTE);
        rrddim_add(stc, "urls",           NULL,  1, 1, RRD_ALGORITHM_ABSOLUTE);
        rrddim_add(stc, "persons_urls",   NULL,  1, 1, RRD_ALGORITHM_ABSOLUTE);
        rrddim_add(stc, "machines_urls",  NULL,  1, 1, RRD_ALGORITHM_ABSOLUTE);
    }
    else rrdset_next(stc);

    rrddim_set(stc, "persons",       registry.persons_count);
    rrddim_set(stc, "machines",      registry.machines_count);
    rrddim_set(stc, "urls",          registry.urls_count);
    rrddim_set(stc, "persons_urls",  registry.persons_urls_count);
    rrddim_set(stc, "machines_urls", registry.machines_urls_count);
    rrdset_done(stc);

    // ------------------------------------------------------------------------

    if(unlikely(!stm)) {
        stm = rrdset_create_localhost(
                "netdata"
                , "registry_mem"
                , NULL
                , "registry"
                , NULL
                , "NetData Registry Memory"
                , "KiB"
                , "registry"
                , "stats"
                , 131300
                , localhost->rrd_update_every
                , RRDSET_TYPE_STACKED
        );

        rrddim_add(stm, "persons",        NULL,  1, 1024, RRD_ALGORITHM_ABSOLUTE);
        rrddim_add(stm, "machines",       NULL,  1, 1024, RRD_ALGORITHM_ABSOLUTE);
        rrddim_add(stm, "urls",           NULL,  1, 1024, RRD_ALGORITHM_ABSOLUTE);
        rrddim_add(stm, "persons_urls",   NULL,  1, 1024, RRD_ALGORITHM_ABSOLUTE);
        rrddim_add(stm, "machines_urls",  NULL,  1, 1024, RRD_ALGORITHM_ABSOLUTE);
    }
    else rrdset_next(stm);

    rrddim_set(stm, "persons",       registry.persons_memory + registry.persons_count * sizeof(NAME_VALUE) + sizeof(DICTIONARY));
    rrddim_set(stm, "machines",      registry.machines_memory + registry.machines_count * sizeof(NAME_VALUE) + sizeof(DICTIONARY));
    rrddim_set(stm, "urls",          registry.urls_memory);
    rrddim_set(stm, "persons_urls",  registry.persons_urls_memory);
    rrddim_set(stm, "machines_urls", registry.machines_urls_memory + registry.machines_count * sizeof(DICTIONARY) + registry.machines_urls_count * sizeof(NAME_VALUE));
    rrdset_done(stm);
}