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
struct TYPE_6__ {scalar_t__ hash_chart; int /*<<< orphan*/  chart; } ;
struct TYPE_5__ {scalar_t__ hash; scalar_t__ hash_name; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDCALC ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rrdcalc_is_matching_this_rrdset(RRDCALC *rc, RRDSET *st) {
    if(     (rc->hash_chart == st->hash      && !strcmp(rc->chart, st->id)) ||
            (rc->hash_chart == st->hash_name && !strcmp(rc->chart, st->name)))
        return 1;

    return 0;
}