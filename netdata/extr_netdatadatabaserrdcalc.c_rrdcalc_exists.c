#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ hash; scalar_t__ hash_chart; scalar_t__ chart; scalar_t__ name; struct TYPE_5__* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  hostname; TYPE_2__* alarms; } ;
typedef  TYPE_1__ RRDHOST ;
typedef  TYPE_2__ RRDCALC ;

/* Variables and functions */
 int /*<<< orphan*/  D_HEALTH ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  info (char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ simple_hash (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

inline int rrdcalc_exists(RRDHOST *host, const char *chart, const char *name, uint32_t hash_chart, uint32_t hash_name) {
    RRDCALC *rc;

    if(unlikely(!chart)) {
        error("attempt to find RRDCALC '%s' without giving a chart name", name);
        return 1;
    }

    if(unlikely(!hash_chart)) hash_chart = simple_hash(chart);
    if(unlikely(!hash_name))  hash_name  = simple_hash(name);

    // make sure it does not already exist
    for(rc = host->alarms; rc ; rc = rc->next) {
        if (unlikely(rc->chart && rc->hash == hash_name && rc->hash_chart == hash_chart && !strcmp(name, rc->name) && !strcmp(chart, rc->chart))) {
            debug(D_HEALTH, "Health alarm '%s.%s' already exists in host '%s'.", chart, name, host->hostname);
            info("Health alarm '%s.%s' already exists in host '%s'.", chart, name, host->hostname);
            return 1;
        }
    }

    return 0;
}