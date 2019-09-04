#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  RRDHOST ;
typedef  int /*<<< orphan*/  PROMETHEUS_OUTPUT_OPTIONS ;
typedef  int /*<<< orphan*/  BUFFER ;
typedef  int /*<<< orphan*/  BACKEND_OPTIONS ;

/* Variables and functions */
 int /*<<< orphan*/  now_realtime_sec () ; 
 int /*<<< orphan*/  prometheus_preparation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrd_stats_api_v1_charts_allmetrics_prometheus (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rrd_stats_api_v1_charts_allmetrics_prometheus_single_host(RRDHOST *host, BUFFER *wb, const char *server, const char *prefix, BACKEND_OPTIONS backend_options, PROMETHEUS_OUTPUT_OPTIONS output_options) {
    time_t before = now_realtime_sec();

    // we start at the point we had stopped before
    time_t after = prometheus_preparation(host, wb, backend_options, server, before, output_options);

    rrd_stats_api_v1_charts_allmetrics_prometheus(host, wb, prefix, backend_options, after, before, 0, output_options);
}