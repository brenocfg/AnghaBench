#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_5__ {unsigned long long tv_sec; int tv_usec; } ;
struct TYPE_4__ {unsigned long long tv_sec; int tv_usec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;
struct global_statistics {int connected_clients; unsigned long long web_requests; unsigned long long web_usec; unsigned long long compressed_content_size; unsigned long long content_size; scalar_t__ rrdr_result_points_generated; scalar_t__ rrdr_db_points_read; scalar_t__ rrdr_queries_made; scalar_t__ web_usec_max; scalar_t__ bytes_sent; scalar_t__ bytes_received; } ;
typedef  int collected_number ;
struct TYPE_6__ {int /*<<< orphan*/  rrd_update_every; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int BITS_IN_A_KILOBIT ; 
 int /*<<< orphan*/  GLOBAL_STATS_RESET_WEB_USEC_MAX ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int /*<<< orphan*/  RUSAGE_THREAD ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  global_statistics_copy (struct global_statistics*,int /*<<< orphan*/ ) ; 
 TYPE_3__* localhost ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void global_statistics_charts(void) {
    static unsigned long long old_web_requests = 0,
                              old_web_usec = 0,
                              old_content_size = 0,
                              old_compressed_content_size = 0;

    static collected_number compression_ratio = -1,
                            average_response_time = -1;

    struct global_statistics gs;
    struct rusage me, thread;

    global_statistics_copy(&gs, GLOBAL_STATS_RESET_WEB_USEC_MAX);
    getrusage(RUSAGE_THREAD, &thread);
    getrusage(RUSAGE_SELF, &me);

    {
        static RRDSET *st_cpu_thread = NULL;
        static RRDDIM *rd_cpu_thread_user = NULL,
                      *rd_cpu_thread_system = NULL;

#ifdef __FreeBSD__
        if (unlikely(!st_cpu_thread)) {
            st_cpu_thread = rrdset_create_localhost(
                    "netdata"
                    , "plugin_freebsd_cpu"
                    , NULL
                    , "freebsd"
                    , NULL
                    , "NetData FreeBSD Plugin CPU usage"
                    , "milliseconds/s"
                    , "netdata"
                    , "stats"
                    , 132000
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_STACKED
            );
#else
        if (unlikely(!st_cpu_thread)) {
            st_cpu_thread = rrdset_create_localhost(
                    "netdata"
                    , "plugin_proc_cpu"
                    , NULL
                    , "proc"
                    , NULL
                    , "NetData Proc Plugin CPU usage"
                    , "milliseconds/s"
                    , "netdata"
                    , "stats"
                    , 132000
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_STACKED
            );
#endif

            rd_cpu_thread_user   = rrddim_add(st_cpu_thread, "user",   NULL, 1, 1000, RRD_ALGORITHM_INCREMENTAL);
            rd_cpu_thread_system = rrddim_add(st_cpu_thread, "system", NULL, 1, 1000, RRD_ALGORITHM_INCREMENTAL);
        }
        else
            rrdset_next(st_cpu_thread);

        rrddim_set_by_pointer(st_cpu_thread, rd_cpu_thread_user,   thread.ru_utime.tv_sec * 1000000ULL + thread.ru_utime.tv_usec);
        rrddim_set_by_pointer(st_cpu_thread, rd_cpu_thread_system, thread.ru_stime.tv_sec * 1000000ULL + thread.ru_stime.tv_usec);
        rrdset_done(st_cpu_thread);
    }

    // ----------------------------------------------------------------

    {
        static RRDSET *st_cpu = NULL;
        static RRDDIM *rd_cpu_user   = NULL,
                      *rd_cpu_system = NULL;

        if (unlikely(!st_cpu)) {
            st_cpu = rrdset_create_localhost(
                    "netdata"
                    , "server_cpu"
                    , NULL
                    , "netdata"
                    , NULL
                    , "NetData CPU usage"
                    , "milliseconds/s"
                    , "netdata"
                    , "stats"
                    , 130000
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_STACKED
            );

            rd_cpu_user   = rrddim_add(st_cpu, "user",   NULL, 1, 1000, RRD_ALGORITHM_INCREMENTAL);
            rd_cpu_system = rrddim_add(st_cpu, "system", NULL, 1, 1000, RRD_ALGORITHM_INCREMENTAL);
        }
        else
            rrdset_next(st_cpu);

        rrddim_set_by_pointer(st_cpu, rd_cpu_user,   me.ru_utime.tv_sec * 1000000ULL + me.ru_utime.tv_usec);
        rrddim_set_by_pointer(st_cpu, rd_cpu_system, me.ru_stime.tv_sec * 1000000ULL + me.ru_stime.tv_usec);
        rrdset_done(st_cpu);
    }

    // ----------------------------------------------------------------

    {
        static RRDSET *st_clients = NULL;
        static RRDDIM *rd_clients = NULL;

        if (unlikely(!st_clients)) {
            st_clients = rrdset_create_localhost(
                    "netdata"
                    , "clients"
                    , NULL
                    , "netdata"
                    , NULL
                    , "NetData Web Clients"
                    , "connected clients"
                    , "netdata"
                    , "stats"
                    , 130200
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_LINE
            );

            rd_clients = rrddim_add(st_clients, "clients", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else
            rrdset_next(st_clients);

        rrddim_set_by_pointer(st_clients, rd_clients, gs.connected_clients);
        rrdset_done(st_clients);
    }

    // ----------------------------------------------------------------

    {
        static RRDSET *st_reqs = NULL;
        static RRDDIM *rd_requests = NULL;

        if (unlikely(!st_reqs)) {
            st_reqs = rrdset_create_localhost(
                    "netdata"
                    , "requests"
                    , NULL
                    , "netdata"
                    , NULL
                    , "NetData Web Requests"
                    , "requests/s"
                    , "netdata"
                    , "stats"
                    , 130300
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_LINE
            );

            rd_requests = rrddim_add(st_reqs, "requests", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else
            rrdset_next(st_reqs);

        rrddim_set_by_pointer(st_reqs, rd_requests, (collected_number) gs.web_requests);
        rrdset_done(st_reqs);
    }

    // ----------------------------------------------------------------

    {
        static RRDSET *st_bytes = NULL;
        static RRDDIM *rd_in = NULL,
                      *rd_out = NULL;

        if (unlikely(!st_bytes)) {
            st_bytes = rrdset_create_localhost(
                    "netdata"
                    , "net"
                    , NULL
                    , "netdata"
                    , NULL
                    , "NetData Network Traffic"
                    , "kilobits/s"
                    , "netdata"
                    , "stats"
                    , 130000
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_AREA
            );

            rd_in  = rrddim_add(st_bytes, "in",  NULL,  8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
            rd_out = rrddim_add(st_bytes, "out", NULL, -8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
        }
        else
            rrdset_next(st_bytes);

        rrddim_set_by_pointer(st_bytes, rd_in, (collected_number) gs.bytes_received);
        rrddim_set_by_pointer(st_bytes, rd_out, (collected_number) gs.bytes_sent);
        rrdset_done(st_bytes);
    }

    // ----------------------------------------------------------------

    {
        static RRDSET *st_duration = NULL;
        static RRDDIM *rd_average = NULL,
                      *rd_max     = NULL;

        if (unlikely(!st_duration)) {
            st_duration = rrdset_create_localhost(
                    "netdata"
                    , "response_time"
                    , NULL
                    , "netdata"
                    , NULL
                    , "NetData API Response Time"
                    , "milliseconds/request"
                    , "netdata"
                    , "stats"
                    , 130400
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_LINE
            );

            rd_average = rrddim_add(st_duration, "average", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
            rd_max = rrddim_add(st_duration, "max", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
        }
        else
            rrdset_next(st_duration);

        uint64_t gweb_usec = gs.web_usec;
        uint64_t gweb_requests = gs.web_requests;

        uint64_t web_usec = (gweb_usec >= old_web_usec) ? gweb_usec - old_web_usec : 0;
        uint64_t web_requests = (gweb_requests >= old_web_requests) ? gweb_requests - old_web_requests : 0;

        old_web_usec = gweb_usec;
        old_web_requests = gweb_requests;

        if (web_requests)
            average_response_time = (collected_number) (web_usec / web_requests);

        if (unlikely(average_response_time != -1))
            rrddim_set_by_pointer(st_duration, rd_average, average_response_time);
        else
            rrddim_set_by_pointer(st_duration, rd_average, 0);

        rrddim_set_by_pointer(st_duration, rd_max, ((gs.web_usec_max)?(collected_number)gs.web_usec_max:average_response_time));
        rrdset_done(st_duration);
    }

    // ----------------------------------------------------------------

    {
        static RRDSET *st_compression = NULL;
        static RRDDIM *rd_savings = NULL;

        if (unlikely(!st_compression)) {
            st_compression = rrdset_create_localhost(
                    "netdata"
                    , "compression_ratio"
                    , NULL
                    , "netdata"
                    , NULL
                    , "NetData API Responses Compression Savings Ratio"
                    , "percentage"
                    , "netdata"
                    , "stats"
                    , 130500
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_LINE
            );

            rd_savings = rrddim_add(st_compression, "savings", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
        }
        else
            rrdset_next(st_compression);

        // since we don't lock here to read the global statistics
        // read the smaller value first
        unsigned long long gcompressed_content_size = gs.compressed_content_size;
        unsigned long long gcontent_size = gs.content_size;

        unsigned long long compressed_content_size = gcompressed_content_size - old_compressed_content_size;
        unsigned long long content_size = gcontent_size - old_content_size;

        old_compressed_content_size = gcompressed_content_size;
        old_content_size = gcontent_size;

        if (content_size && content_size >= compressed_content_size)
            compression_ratio = ((content_size - compressed_content_size) * 100 * 1000) / content_size;

        if (compression_ratio != -1)
            rrddim_set_by_pointer(st_compression, rd_savings, compression_ratio);

        rrdset_done(st_compression);
    }

    // ----------------------------------------------------------------

    if(gs.rrdr_queries_made) {
        static RRDSET *st_rrdr_queries = NULL;
        static RRDDIM *rd_queries = NULL;

        if (unlikely(!st_rrdr_queries)) {
            st_rrdr_queries = rrdset_create_localhost(
                    "netdata"
                    , "queries"
                    , NULL
                    , "queries"
                    , NULL
                    , "NetData API Queries"
                    , "queries/s"
                    , "netdata"
                    , "stats"
                    , 130500
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_LINE
            );

            rd_queries = rrddim_add(st_rrdr_queries, "queries", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else
            rrdset_next(st_rrdr_queries);

        rrddim_set_by_pointer(st_rrdr_queries, rd_queries, (collected_number)gs.rrdr_queries_made);

        rrdset_done(st_rrdr_queries);
    }

    // ----------------------------------------------------------------

    if(gs.rrdr_db_points_read || gs.rrdr_result_points_generated) {
        static RRDSET *st_rrdr_points = NULL;
        static RRDDIM *rd_points_read = NULL;
        static RRDDIM *rd_points_generated = NULL;

        if (unlikely(!st_rrdr_points)) {
            st_rrdr_points = rrdset_create_localhost(
                    "netdata"
                    , "db_points"
                    , NULL
                    , "queries"
                    , NULL
                    , "NetData API Points"
                    , "points/s"
                    , "netdata"
                    , "stats"
                    , 130501
                    , localhost->rrd_update_every
                    , RRDSET_TYPE_AREA
            );

            rd_points_read = rrddim_add(st_rrdr_points, "read", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_points_generated = rrddim_add(st_rrdr_points, "generated", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else
            rrdset_next(st_rrdr_points);

        rrddim_set_by_pointer(st_rrdr_points, rd_points_read, (collected_number)gs.rrdr_db_points_read);
        rrddim_set_by_pointer(st_rrdr_points, rd_points_generated, (collected_number)gs.rrdr_result_points_generated);

        rrdset_done(st_rrdr_points);
    }
}