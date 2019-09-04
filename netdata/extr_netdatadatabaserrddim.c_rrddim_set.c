#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  collected_number ;
struct TYPE_7__ {int /*<<< orphan*/  hostname; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  id; TYPE_2__* rrdhost; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDHOST ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrddim_find (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

collected_number rrddim_set(RRDSET *st, const char *id, collected_number value) {
    RRDHOST *host = st->rrdhost;
    RRDDIM *rd = rrddim_find(st, id);
    if(unlikely(!rd)) {
        error("Cannot find dimension with id '%s' on stats '%s' (%s) on host '%s'.", id, st->name, st->id, host->hostname);
        return 0;
    }

    return rrddim_set_by_pointer(st, rd, value);
}