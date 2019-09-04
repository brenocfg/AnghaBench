#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ STATSD_METRIC ;

/* Variables and functions */
 int /*<<< orphan*/  STATSD_CHART_PREFIX ; 
 int /*<<< orphan*/  netdata_fix_chart_id (char*) ; 
 int /*<<< orphan*/  snprintfz (char*,size_t,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpyz (char*,char const*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void statsd_get_metric_type_and_id(STATSD_METRIC *m, char *type, char *id, const char *defid, size_t len) {
    char *s;

    snprintfz(type, len, "%s_%s_%s", STATSD_CHART_PREFIX, defid, m->name);
    for(s = type; *s ;s++)
        if(unlikely(*s == '.')) break;

    if(*s == '.') {
        *s++ = '\0';
        strncpyz(id, s, len);
    }
    else {
        strncpyz(id, defid, len);
    }

    netdata_fix_chart_id(type);
    netdata_fix_chart_id(id);
}