#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ histogram_increase_step; } ;
struct TYPE_9__ {TYPE_1__* ext; } ;
struct TYPE_10__ {int reset; int /*<<< orphan*/  count; int /*<<< orphan*/  events; TYPE_2__ histogram; } ;
struct TYPE_8__ {int used; int size; double* values; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ STATSD_METRIC ;
typedef  double LONG_DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  is_metric_useful_for_collection (TYPE_3__*) ; 
 int isgreater (double,double) ; 
 int isless (double,double) ; 
 long long llrintl (double) ; 
 int /*<<< orphan*/  netdata_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdata_mutex_unlock (int /*<<< orphan*/ *) ; 
 double* reallocz (double*,int) ; 
 TYPE_6__ statsd ; 
 double statsd_parse_float (char const*,double) ; 
 double statsd_parse_sampling_rate (char const*) ; 
 int /*<<< orphan*/  statsd_reset_metric (TYPE_3__*) ; 
 scalar_t__ unlikely (int) ; 
 int value_is_zinit (char const*) ; 

__attribute__((used)) static inline void statsd_process_histogram_or_timer(STATSD_METRIC *m, const char *value, const char *sampling, const char *type) {
    if(!is_metric_useful_for_collection(m)) return;

    if(unlikely(!value || !*value)) {
        error("STATSD: metric of type %s, with empty value is ignored.", type);
        return;
    }

    if(unlikely(m->reset)) {
        m->histogram.ext->used = 0;
        statsd_reset_metric(m);
    }

    if(unlikely(value_is_zinit(value))) {
        // magic loading of metric, without affecting anything
    }
    else {
        LONG_DOUBLE v = statsd_parse_float(value, 1.0);
        LONG_DOUBLE sampling_rate = statsd_parse_sampling_rate(sampling);
        if(unlikely(isless(sampling_rate, 0.01))) sampling_rate = 0.01;
        if(unlikely(isgreater(sampling_rate, 1.0))) sampling_rate = 1.0;

        long long samples = llrintl(1.0 / sampling_rate);
        while(samples-- > 0) {

            if(unlikely(m->histogram.ext->used == m->histogram.ext->size)) {
                netdata_mutex_lock(&m->histogram.ext->mutex);
                m->histogram.ext->size += statsd.histogram_increase_step;
                m->histogram.ext->values = reallocz(m->histogram.ext->values, sizeof(LONG_DOUBLE) * m->histogram.ext->size);
                netdata_mutex_unlock(&m->histogram.ext->mutex);
            }

            m->histogram.ext->values[m->histogram.ext->used++] = v;
        }

        m->events++;
        m->count++;
    }
}