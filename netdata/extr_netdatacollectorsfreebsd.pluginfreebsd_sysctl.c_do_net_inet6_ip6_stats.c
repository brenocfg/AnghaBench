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
typedef  int /*<<< orphan*/  usec_t ;
struct ip6stat {scalar_t__ ip6s_noroute; scalar_t__ ip6s_cantforward; scalar_t__ ip6s_tooshort; scalar_t__ ip6s_sources_none; scalar_t__ ip6s_exthdrtoolong; scalar_t__ ip6s_badvers; scalar_t__ ip6s_badoptions; scalar_t__ ip6s_odropped; scalar_t__ ip6s_toosmall; scalar_t__ ip6s_fragments; scalar_t__ ip6s_fragtimeout; scalar_t__ ip6s_fragdropped; scalar_t__ ip6s_reassembled; scalar_t__ ip6s_ofragments; scalar_t__ ip6s_cantfrag; scalar_t__ ip6s_fragmented; scalar_t__ ip6s_delivered; scalar_t__ ip6s_forward; scalar_t__ ip6s_total; scalar_t__ ip6s_localout; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int CONFIG_BOOLEAN_AUTO ; 
 int CONFIG_BOOLEAN_YES ; 
 int GETSYSCTL_SIMPLE (char*,int*,struct ip6stat) ; 
 int /*<<< orphan*/  RRDSET_FLAG_DETAIL ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int config_get_boolean_ondemand (char*,char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_net_inet6_ip6_stats(int update_every, usec_t dt) {
    (void)dt;
    static int do_ip6_packets = -1, do_ip6_fragsout = -1, do_ip6_fragsin = -1, do_ip6_errors = -1;

    if (unlikely(do_ip6_packets == -1)) {
        do_ip6_packets  = config_get_boolean_ondemand("plugin:freebsd:net.inet6.ip6.stats", "ipv6 packets",
                                                      CONFIG_BOOLEAN_AUTO);
        do_ip6_fragsout = config_get_boolean_ondemand("plugin:freebsd:net.inet6.ip6.stats", "ipv6 fragments sent",
                                                      CONFIG_BOOLEAN_AUTO);
        do_ip6_fragsin  = config_get_boolean_ondemand("plugin:freebsd:net.inet6.ip6.stats", "ipv6 fragments assembly",
                                                      CONFIG_BOOLEAN_AUTO);
        do_ip6_errors   = config_get_boolean_ondemand("plugin:freebsd:net.inet6.ip6.stats", "ipv6 errors",
                                                      CONFIG_BOOLEAN_AUTO);
    }

    if (likely(do_ip6_packets || do_ip6_fragsout || do_ip6_fragsin || do_ip6_errors)) {
        static int mib[4] = {0, 0, 0, 0};
        struct ip6stat ip6stat;

        if (unlikely(GETSYSCTL_SIMPLE("net.inet6.ip6.stats", mib, ip6stat))) {
            do_ip6_packets = 0;
            error("DISABLED: ipv6.packets chart");
            do_ip6_fragsout = 0;
            error("DISABLED: ipv6.fragsout chart");
            do_ip6_fragsin = 0;
            error("DISABLED: ipv6.fragsin chart");
            do_ip6_errors = 0;
            error("DISABLED: ipv6.errors chart");
            error("DISABLED: net.inet6.ip6.stats module");
            return 1;
        } else {

            // --------------------------------------------------------------------

            if (do_ip6_packets == CONFIG_BOOLEAN_YES || (do_ip6_packets == CONFIG_BOOLEAN_AUTO &&
                                                         (ip6stat.ip6s_localout || ip6stat.ip6s_total ||
                                                          ip6stat.ip6s_forward || ip6stat.ip6s_delivered))) {
                do_ip6_packets = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_received = NULL, *rd_sent = NULL, *rd_forwarded = NULL, *rd_delivers = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "packets",
                            NULL,
                            "packets",
                            NULL,
                            "IPv6 Packets",
                            "packets/s",
                            "freebsd.plugin",
                            "net.inet6.ip6.stats",
                            3000,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rd_received  = rrddim_add(st, "received",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_sent      = rrddim_add(st, "sent",      NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_forwarded = rrddim_add(st, "forwarded", NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_delivers  = rrddim_add(st, "delivers",  NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_sent,      ip6stat.ip6s_localout);
                rrddim_set_by_pointer(st, rd_received,  ip6stat.ip6s_total);
                rrddim_set_by_pointer(st, rd_forwarded, ip6stat.ip6s_forward);
                rrddim_set_by_pointer(st, rd_delivers,  ip6stat.ip6s_delivered);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (do_ip6_fragsout == CONFIG_BOOLEAN_YES || (do_ip6_fragsout == CONFIG_BOOLEAN_AUTO &&
                                                          (ip6stat.ip6s_fragmented || ip6stat.ip6s_cantfrag ||
                                                           ip6stat.ip6s_ofragments))) {
                do_ip6_fragsout = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_ok = NULL, *rd_failed = NULL, *rd_all = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                             "fragsout",
                             NULL,
                             "fragments",
                             NULL,
                             "IPv6 Fragments Sent",
                             "packets/s",
                             "freebsd.plugin",
                             "net.inet6.ip6.stats",
                             3010,
                             update_every,
                             RRDSET_TYPE_LINE
                    );

                    rrdset_flag_set(st, RRDSET_FLAG_DETAIL);

                    rd_ok     = rrddim_add(st, "ok",     NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_failed = rrddim_add(st, "failed", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_all    = rrddim_add(st, "all",    NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_ok,     ip6stat.ip6s_fragmented);
                rrddim_set_by_pointer(st, rd_failed, ip6stat.ip6s_cantfrag);
                rrddim_set_by_pointer(st, rd_all,    ip6stat.ip6s_ofragments);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (do_ip6_fragsin == CONFIG_BOOLEAN_YES || (do_ip6_fragsin == CONFIG_BOOLEAN_AUTO &&
                                                         (ip6stat.ip6s_reassembled || ip6stat.ip6s_fragdropped ||
                                                          ip6stat.ip6s_fragtimeout || ip6stat.ip6s_fragments))) {
                do_ip6_fragsin = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_ok = NULL, *rd_failed = NULL, *rd_timeout = NULL, *rd_all = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "fragsin",
                            NULL,
                            "fragments",
                            NULL,
                            "IPv6 Fragments Reassembly",
                            "packets/s",
                            "freebsd.plugin",
                            "net.inet6.ip6.stats",
                            3011,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rrdset_flag_set(st, RRDSET_FLAG_DETAIL);

                    rd_ok      = rrddim_add(st, "ok",      NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_failed  = rrddim_add(st, "failed",  NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_timeout = rrddim_add(st, "timeout", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_all     = rrddim_add(st, "all",     NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_ok,      ip6stat.ip6s_reassembled);
                rrddim_set_by_pointer(st, rd_failed,  ip6stat.ip6s_fragdropped);
                rrddim_set_by_pointer(st, rd_timeout, ip6stat.ip6s_fragtimeout);
                rrddim_set_by_pointer(st, rd_all,     ip6stat.ip6s_fragments);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (do_ip6_errors == CONFIG_BOOLEAN_YES || (do_ip6_errors == CONFIG_BOOLEAN_AUTO && (
                    ip6stat.ip6s_toosmall ||
                    ip6stat.ip6s_odropped ||
                    ip6stat.ip6s_badoptions ||
                    ip6stat.ip6s_badvers ||
                    ip6stat.ip6s_exthdrtoolong ||
                    ip6stat.ip6s_sources_none ||
                    ip6stat.ip6s_tooshort ||
                    ip6stat.ip6s_cantforward ||
                    ip6stat.ip6s_noroute))) {
                do_ip6_errors = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_in_discards = NULL, *rd_out_discards = NULL,
                              *rd_in_hdr_errors = NULL, *rd_in_addr_errors = NULL, *rd_in_truncated_pkts = NULL,
                              *rd_in_no_routes = NULL, *rd_out_no_routes = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "errors",
                            NULL,
                            "errors",
                            NULL,
                            "IPv6 Errors",
                            "packets/s",
                            "freebsd.plugin",
                            "net.inet6.ip6.stats",
                            3002,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rrdset_flag_set(st, RRDSET_FLAG_DETAIL);

                    rd_in_discards       = rrddim_add(st, "InDiscards",      NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_discards      = rrddim_add(st, "OutDiscards",     NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_hdr_errors     = rrddim_add(st, "InHdrErrors",     NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_addr_errors    = rrddim_add(st, "InAddrErrors",    NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_truncated_pkts = rrddim_add(st, "InTruncatedPkts", NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_no_routes      = rrddim_add(st, "InNoRoutes",      NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_no_routes     = rrddim_add(st, "OutNoRoutes",     NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_in_discards,       ip6stat.ip6s_toosmall);
                rrddim_set_by_pointer(st, rd_out_discards,      ip6stat.ip6s_odropped);
                rrddim_set_by_pointer(st, rd_in_hdr_errors,     ip6stat.ip6s_badoptions + ip6stat.ip6s_badvers +
                                                                ip6stat.ip6s_exthdrtoolong);
                rrddim_set_by_pointer(st, rd_in_addr_errors,    ip6stat.ip6s_sources_none);
                rrddim_set_by_pointer(st, rd_in_truncated_pkts, ip6stat.ip6s_tooshort);
                rrddim_set_by_pointer(st, rd_in_no_routes,      ip6stat.ip6s_cantforward);
                rrddim_set_by_pointer(st, rd_out_no_routes,     ip6stat.ip6s_noroute);
                rrdset_done(st);
            }
        }
    } else {
        error("DISABLED: net.inet6.ip6.stats module");
        return 1;
    }

    return 0;
}