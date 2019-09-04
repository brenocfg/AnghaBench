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
struct TYPE_8__ {scalar_t__ algorithm; scalar_t__ exposed; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
typedef  scalar_t__ RRD_ALGORITHM ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  D_RRD_CALLS ; 
 int /*<<< orphan*/  RRDSET_FLAG_HOMEGENEOUS_CHECK ; 
 int /*<<< orphan*/  RRDSET_FLAG_UPSTREAM_EXPOSED ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrd_algorithm_name (scalar_t__) ; 
 int /*<<< orphan*/  rrdset_flag_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_flag_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

inline int rrddim_set_algorithm(RRDSET *st, RRDDIM *rd, RRD_ALGORITHM algorithm) {
    if(unlikely(rd->algorithm == algorithm))
        return 0;

    debug(D_RRD_CALLS, "Updating algorithm of dimension '%s/%s' from %s to %s", st->id, rd->name, rrd_algorithm_name(rd->algorithm), rrd_algorithm_name(algorithm));
    rd->algorithm = algorithm;
    rd->exposed = 0;
    rrdset_flag_set(st, RRDSET_FLAG_HOMEGENEOUS_CHECK);
    rrdset_flag_clear(st, RRDSET_FLAG_UPSTREAM_EXPOSED);
    return 1;
}