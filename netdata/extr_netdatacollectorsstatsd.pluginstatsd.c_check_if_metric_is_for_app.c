#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_4__* apps; } ;
struct TYPE_16__ {int default_options; scalar_t__ dict; TYPE_3__* charts; int /*<<< orphan*/  name; int /*<<< orphan*/  metrics; struct TYPE_16__* next; } ;
struct TYPE_15__ {TYPE_2__* dimensions; struct TYPE_15__* next; } ;
struct TYPE_14__ {int metric_pattern; char* name; scalar_t__ metric_hash; int /*<<< orphan*/  metric; int /*<<< orphan*/  value_ptr; int /*<<< orphan*/  value_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  divisor; int /*<<< orphan*/  multiplier; struct TYPE_14__* next; } ;
struct TYPE_13__ {char* name; int options; scalar_t__ hash; } ;
typedef  TYPE_1__ STATSD_METRIC ;
typedef  int /*<<< orphan*/  STATSD_INDEX ;
typedef  TYPE_2__ STATSD_APP_CHART_DIM ;
typedef  TYPE_3__ STATSD_APP_CHART ;
typedef  TYPE_4__ STATSD_APP ;

/* Variables and functions */
 int /*<<< orphan*/  D_STATSD ; 
 int STATSD_METRIC_OPTION_PRIVATE_CHART_CHECKED ; 
 int STATSD_METRIC_OPTION_PRIVATE_CHART_ENABLED ; 
 int STATSD_METRIC_OPTION_SHOW_GAPS_WHEN_NOT_COLLECTED ; 
 int /*<<< orphan*/  add_dimension_to_app_chart (TYPE_4__*,TYPE_3__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 char* dictionary_get (scalar_t__,char*) ; 
 scalar_t__ likely (char) ; 
 int /*<<< orphan*/  link_metric_to_app_dimension (TYPE_4__*,TYPE_1__*,TYPE_3__*,TYPE_2__*) ; 
 int simple_pattern_matches (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ simple_pattern_matches_extract (int,char*,char*,size_t) ; 
 TYPE_5__ statsd ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void check_if_metric_is_for_app(STATSD_INDEX *index, STATSD_METRIC *m) {
    (void)index;

    STATSD_APP *app;
    for(app = statsd.apps; app ;app = app->next) {
        if(unlikely(simple_pattern_matches(app->metrics, m->name))) {
            debug(D_STATSD, "metric '%s' matches app '%s'", m->name, app->name);

            // the metric should get the options from the app

            if(app->default_options & STATSD_METRIC_OPTION_PRIVATE_CHART_ENABLED)
                m->options |= STATSD_METRIC_OPTION_PRIVATE_CHART_ENABLED;
            else
                m->options &= ~STATSD_METRIC_OPTION_PRIVATE_CHART_ENABLED;

            if(app->default_options & STATSD_METRIC_OPTION_SHOW_GAPS_WHEN_NOT_COLLECTED)
                m->options |= STATSD_METRIC_OPTION_SHOW_GAPS_WHEN_NOT_COLLECTED;
            else
                m->options &= ~STATSD_METRIC_OPTION_SHOW_GAPS_WHEN_NOT_COLLECTED;

            m->options |= STATSD_METRIC_OPTION_PRIVATE_CHART_CHECKED;

            // check if there is a chart in this app, willing to get this metric
            STATSD_APP_CHART *chart;
            for(chart = app->charts; chart; chart = chart->next) {

                STATSD_APP_CHART_DIM *dim;
                for(dim = chart->dimensions; dim ; dim = dim->next) {
                    if(unlikely(dim->metric_pattern)) {
                        size_t dim_name_len = strlen(dim->name);
                        size_t wildcarded_len = dim_name_len + strlen(m->name) + 1;
                        char wildcarded[wildcarded_len];

                        strcpy(wildcarded, dim->name);
                        char *ws = &wildcarded[dim_name_len];

                        if(simple_pattern_matches_extract(dim->metric_pattern, m->name, ws, wildcarded_len - dim_name_len)) {

                            char *final_name = NULL;

                            if(app->dict) {
                                if(likely(*wildcarded)) {
                                    // use the name of the wildcarded string
                                    final_name = dictionary_get(app->dict, wildcarded);
                                }

                                if(unlikely(!final_name)) {
                                    // use the name of the metric
                                    final_name = dictionary_get(app->dict, m->name);
                                }
                            }

                            if(unlikely(!final_name))
                                final_name = wildcarded;

                            add_dimension_to_app_chart(
                                    app
                                    , chart
                                    , m->name
                                    , final_name
                                    , dim->multiplier
                                    , dim->divisor
                                    , dim->flags
                                    , dim->value_type
                            );

                            // the new dimension is appended to the list
                            // so, it will be matched and linked later too
                        }
                    }
                    else if(!dim->value_ptr && dim->metric_hash == m->hash && !strcmp(dim->metric, m->name)) {
                        // we have a match - this metric should be linked to this dimension
                        link_metric_to_app_dimension(app, m, chart, dim);
                    }
                }

            }
        }
    }
}