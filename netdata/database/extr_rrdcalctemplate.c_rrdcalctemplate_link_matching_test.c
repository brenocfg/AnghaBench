#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* chart; char* name; int /*<<< orphan*/  foreachdim; TYPE_1__* rrdset; } ;
struct TYPE_13__ {scalar_t__ hash_context; int /*<<< orphan*/  name; int /*<<< orphan*/  family_pattern; int /*<<< orphan*/  context; } ;
struct TYPE_12__ {int /*<<< orphan*/  hostname; } ;
struct TYPE_11__ {scalar_t__ hash_context; int /*<<< orphan*/  id; int /*<<< orphan*/  family; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDHOST ;
typedef  TYPE_3__ RRDCALCTEMPLATE ;
typedef  TYPE_4__ RRDCALC ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* rrdcalc_create_from_template (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ simple_pattern_matches (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void rrdcalctemplate_link_matching_test(RRDCALCTEMPLATE *rt, RRDSET *st, RRDHOST *host ) {
    if(rt->hash_context == st->hash_context && !strcmp(rt->context, st->context)
       && (!rt->family_pattern || simple_pattern_matches(rt->family_pattern, st->family))) {
        RRDCALC *rc = rrdcalc_create_from_template(host, rt, st->id);
        if(unlikely(!rc))
            info("Health tried to create alarm from template '%s' on chart '%s' of host '%s', but it failed", rt->name, st->id, host->hostname);
#ifdef NETDATA_INTERNAL_CHECKS
        else if(rc->rrdset != st && !rc->foreachdim) //When we have a template with foreadhdim, the child will be added to the index late
            error("Health alarm '%s.%s' should be linked to chart '%s', but it is not", rc->chart?rc->chart:"NOCHART", rc->name, st->id);
#endif
    }
}