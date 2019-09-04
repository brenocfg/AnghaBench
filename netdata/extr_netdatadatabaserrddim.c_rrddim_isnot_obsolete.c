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
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  D_RRD_CALLS ; 
 int /*<<< orphan*/  RRDDIM_FLAG_OBSOLETE ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_flag_clear (TYPE_2__*,int /*<<< orphan*/ ) ; 

inline void rrddim_isnot_obsolete(RRDSET *st, RRDDIM *rd) {
    debug(D_RRD_CALLS, "rrddim_isnot_obsolete() for chart %s, dimension %s", st->name, rd->name);

    rrddim_flag_clear(rd, RRDDIM_FLAG_OBSOLETE);
}