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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  avl ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  hash; } ;
struct TYPE_5__ {int /*<<< orphan*/  alarms_idx_name; } ;
typedef  TYPE_1__ RRDHOST ;
typedef  TYPE_2__ RRDCALC ;

/* Variables and functions */
 scalar_t__ avl_search_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

RRDCALC *alarm_max_last_repeat(RRDHOST *host, char *alarm_name,uint32_t hash) {
    RRDCALC findme;
    findme.name = alarm_name;
    findme.hash = hash;
    RRDCALC *rc = (RRDCALC *)avl_search_lock(&host->alarms_idx_name, (avl *)&findme);

    return rc;
}