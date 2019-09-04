#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ hash; int /*<<< orphan*/  name; struct TYPE_6__* rrdset_next; } ;
struct TYPE_5__ {TYPE_2__* alarms; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDCALC ;

/* Variables and functions */
 scalar_t__ simple_hash (char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ unlikely (int) ; 

RRDCALC *rrdcalc_find(RRDSET *st, const char *name) {
    RRDCALC *rc;
    uint32_t hash = simple_hash(name);

    for( rc = st->alarms; rc ; rc = rc->rrdset_next ) {
        if(unlikely(rc->hash == hash && !strcmp(rc->name, name)))
            return rc;
    }

    return NULL;
}