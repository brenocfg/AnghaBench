#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long private_charts_rrd_history_entries; scalar_t__ private_charts; scalar_t__ max_private_charts; scalar_t__ private_charts_hidden; int /*<<< orphan*/  private_charts_memory_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ STATSD_METRIC ;
typedef  int /*<<< orphan*/  RRD_MEMORY_MODE ;
typedef  int /*<<< orphan*/  RRDSET_TYPE ;
typedef  int /*<<< orphan*/  RRDSET ;

/* Variables and functions */
 int /*<<< orphan*/  D_STATSD ; 
 int /*<<< orphan*/  PLUGIN_STATSD_NAME ; 
 int /*<<< orphan*/  RRDSET_FLAG_HIDDEN ; 
 int /*<<< orphan*/  RRDSET_FLAG_STORE_FIRST ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_NONE ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  localhost ; 
 int /*<<< orphan*/ * rrdset_create_custom (int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,char*,long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  rrdset_flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ statsd ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline RRDSET *statsd_private_rrdset_create(
        STATSD_METRIC *m
        , const char *type
        , const char *id
        , const char *name
        , const char *family
        , const char *context
        , const char *title
        , const char *units
        , long priority
        , int update_every
        , RRDSET_TYPE chart_type
) {
    RRD_MEMORY_MODE memory_mode = statsd.private_charts_memory_mode;
    long history = statsd.private_charts_rrd_history_entries;

    if(unlikely(statsd.private_charts >= statsd.max_private_charts)) {
        debug(D_STATSD, "STATSD: metric '%s' will be charted with memory mode = none, because the maximum number of charts has been reached.", m->name);
        info("STATSD: metric '%s' will be charted with memory mode = none, because the maximum number of charts (%zu) has been reached. Increase the number of charts by editing netdata.conf, [statsd] section.", m->name, statsd.max_private_charts);
        memory_mode = RRD_MEMORY_MODE_NONE;
        history = 5;
    }

    statsd.private_charts++;
    RRDSET *st = rrdset_create_custom(
            localhost         // host
            , type            // type
            , id              // id
            , name            // name
            , family          // family
            , context         // context
            , title           // title
            , units           // units
            , PLUGIN_STATSD_NAME // plugin
            , "private_chart" // module
            , priority        // priority
            , update_every    // update every
            , chart_type      // chart type
            , memory_mode     // memory mode
            , history         // history
    );
    rrdset_flag_set(st, RRDSET_FLAG_STORE_FIRST);

    if(statsd.private_charts_hidden)
        rrdset_flag_set(st, RRDSET_FLAG_HIDDEN);

    // rrdset_flag_set(st, RRDSET_FLAG_DEBUG);
    return st;
}