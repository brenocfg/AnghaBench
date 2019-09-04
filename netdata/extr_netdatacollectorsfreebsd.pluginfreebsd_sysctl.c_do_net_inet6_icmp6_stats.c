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
typedef  scalar_t__ u_long ;
struct icmp6stat {scalar_t__* icp6s_outhist; scalar_t__* icp6s_inhist; scalar_t__ icp6s_badlen; scalar_t__ icp6s_checksum; scalar_t__ icp6s_error; scalar_t__ icp6s_tooshort; scalar_t__ icp6s_badcode; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int CONFIG_BOOLEAN_AUTO ; 
 int CONFIG_BOOLEAN_YES ; 
 int GETSYSCTL_SIMPLE (char*,int*,struct icmp6stat) ; 
 size_t ICMP6_DST_UNREACH ; 
 size_t ICMP6_ECHO_REPLY ; 
 size_t ICMP6_ECHO_REQUEST ; 
 int ICMP6_MAXTYPE ; 
 size_t ICMP6_PARAM_PROB ; 
 size_t ICMP6_TIME_EXCEEDED ; 
 size_t ND_NEIGHBOR_ADVERT ; 
 size_t ND_NEIGHBOR_SOLICIT ; 
 size_t ND_REDIRECT ; 
 size_t ND_ROUTER_ADVERT ; 
 size_t ND_ROUTER_SOLICIT ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int config_get_boolean_ondemand (char*,char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_net_inet6_icmp6_stats(int update_every, usec_t dt) {
    (void)dt;
    static int do_icmp6 = -1, do_icmp6_redir = -1, do_icmp6_errors = -1, do_icmp6_echos = -1, do_icmp6_router = -1,
            do_icmp6_neighbor = -1, do_icmp6_types = -1;

    if (unlikely(do_icmp6 == -1)) {
        do_icmp6          = config_get_boolean_ondemand("plugin:freebsd:net.inet6.icmp6.stats", "icmp",
                                                        CONFIG_BOOLEAN_AUTO);
        do_icmp6_redir    = config_get_boolean_ondemand("plugin:freebsd:net.inet6.icmp6.stats", "icmp redirects",
                                                        CONFIG_BOOLEAN_AUTO);
        do_icmp6_errors   = config_get_boolean_ondemand("plugin:freebsd:net.inet6.icmp6.stats", "icmp errors",
                                                        CONFIG_BOOLEAN_AUTO);
        do_icmp6_echos    = config_get_boolean_ondemand("plugin:freebsd:net.inet6.icmp6.stats", "icmp echos",
                                                        CONFIG_BOOLEAN_AUTO);
        do_icmp6_router   = config_get_boolean_ondemand("plugin:freebsd:net.inet6.icmp6.stats", "icmp router",
                                                        CONFIG_BOOLEAN_AUTO);
        do_icmp6_neighbor = config_get_boolean_ondemand("plugin:freebsd:net.inet6.icmp6.stats", "icmp neighbor",
                                                        CONFIG_BOOLEAN_AUTO);
        do_icmp6_types    = config_get_boolean_ondemand("plugin:freebsd:net.inet6.icmp6.stats", "icmp types",
                                                        CONFIG_BOOLEAN_AUTO);
    }

    if (likely(do_icmp6 || do_icmp6_redir || do_icmp6_errors || do_icmp6_echos || do_icmp6_router || do_icmp6_neighbor || do_icmp6_types)) {
        static int mib[4] = {0, 0, 0, 0};
        struct icmp6stat icmp6stat;

        if (unlikely(GETSYSCTL_SIMPLE("net.inet6.icmp6.stats", mib, icmp6stat))) {
            do_icmp6 = 0;
            error("DISABLED: ipv6.icmp chart");
            do_icmp6_redir = 0;
            error("DISABLED: ipv6.icmpredir chart");
            do_icmp6_errors = 0;
            error("DISABLED: ipv6.icmperrors chart");
            do_icmp6_echos = 0;
            error("DISABLED: ipv6.icmpechos chart");
            do_icmp6_router = 0;
            error("DISABLED: ipv6.icmprouter chart");
            do_icmp6_neighbor = 0;
            error("DISABLED: ipv6.icmpneighbor chart");
            do_icmp6_types = 0;
            error("DISABLED: ipv6.icmptypes chart");
            error("DISABLED: net.inet6.icmp6.stats module");
            return 1;
        } else {
            int i;
            struct icmp6_total {
                u_long  msgs_in;
                u_long  msgs_out;
            } icmp6_total = {0, 0};

            for (i = 0; i <= ICMP6_MAXTYPE; i++) {
                icmp6_total.msgs_in += icmp6stat.icp6s_inhist[i];
                icmp6_total.msgs_out += icmp6stat.icp6s_outhist[i];
            }
            icmp6_total.msgs_in += icmp6stat.icp6s_badcode + icmp6stat.icp6s_badlen + icmp6stat.icp6s_checksum + icmp6stat.icp6s_tooshort;

            // --------------------------------------------------------------------

            if (do_icmp6 == CONFIG_BOOLEAN_YES || (do_icmp6 == CONFIG_BOOLEAN_AUTO && (icmp6_total.msgs_in || icmp6_total.msgs_out))) {
                do_icmp6 = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_received = NULL, *rd_sent = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "icmp",
                            NULL,
                            "icmp",
                            NULL,
                            "IPv6 ICMP Messages",
                            "messages/s",
                            "freebsd.plugin",
                            "net.inet6.icmp6.stats",
                            10000,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rd_received = rrddim_add(st, "received", NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_sent     = rrddim_add(st, "sent",     NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_received, icmp6_total.msgs_out);
                rrddim_set_by_pointer(st, rd_sent,     icmp6_total.msgs_in);

                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (do_icmp6_redir == CONFIG_BOOLEAN_YES || (do_icmp6_redir == CONFIG_BOOLEAN_AUTO && (icmp6stat.icp6s_inhist[ND_REDIRECT] || icmp6stat.icp6s_outhist[ND_REDIRECT]))) {
                do_icmp6_redir = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_received = NULL, *rd_sent = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "icmpredir",
                            NULL,
                            "icmp",
                            NULL,
                            "IPv6 ICMP Redirects",
                            "redirects/s",
                            "freebsd.plugin",
                            "net.inet6.icmp6.stats",
                            10050,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rd_received = rrddim_add(st, "received", NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_sent     = rrddim_add(st, "sent",     NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_received, icmp6stat.icp6s_outhist[ND_REDIRECT]);
                rrddim_set_by_pointer(st, rd_sent, icmp6stat.icp6s_inhist[ND_REDIRECT]);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (do_icmp6_errors == CONFIG_BOOLEAN_YES || (do_icmp6_errors == CONFIG_BOOLEAN_AUTO && (
                    icmp6stat.icp6s_badcode ||
                    icmp6stat.icp6s_badlen ||
                    icmp6stat.icp6s_checksum ||
                    icmp6stat.icp6s_tooshort ||
                    icmp6stat.icp6s_error ||
                    icmp6stat.icp6s_inhist[ICMP6_DST_UNREACH] ||
                    icmp6stat.icp6s_inhist[ICMP6_TIME_EXCEEDED] ||
                    icmp6stat.icp6s_inhist[ICMP6_PARAM_PROB] ||
                    icmp6stat.icp6s_outhist[ICMP6_DST_UNREACH] ||
                    icmp6stat.icp6s_outhist[ICMP6_TIME_EXCEEDED] ||
                    icmp6stat.icp6s_outhist[ICMP6_PARAM_PROB]))) {
                do_icmp6_errors = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_in_errors = NULL, *rd_out_errors = NULL, *rd_in_csum_errors = NULL,
                              *rd_in_dest_unreachs = NULL, *rd_in_pkt_too_bigs = NULL, *rd_in_time_excds = NULL,
                              *rd_in_parm_problems = NULL, *rd_out_dest_unreachs = NULL, *rd_out_time_excds = NULL,
                              *rd_out_parm_problems = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "icmperrors",
                            NULL, "icmp",
                            NULL,
                            "IPv6 ICMP Errors",
                            "errors/s",
                            "freebsd.plugin",
                            "net.inet6.icmp6.stats",
                            10100,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rd_in_errors         = rrddim_add(st, "InErrors",        NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_errors        = rrddim_add(st, "OutErrors",       NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_csum_errors    = rrddim_add(st, "InCsumErrors",    NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_dest_unreachs  = rrddim_add(st, "InDestUnreachs",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_pkt_too_bigs   = rrddim_add(st, "InPktTooBigs",    NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_time_excds     = rrddim_add(st, "InTimeExcds",     NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_parm_problems  = rrddim_add(st, "InParmProblems",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_dest_unreachs = rrddim_add(st, "OutDestUnreachs", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_time_excds    = rrddim_add(st, "OutTimeExcds",    NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_parm_problems = rrddim_add(st, "OutParmProblems", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_in_errors,         icmp6stat.icp6s_badcode + icmp6stat.icp6s_badlen +
                                                                icmp6stat.icp6s_checksum + icmp6stat.icp6s_tooshort);
                rrddim_set_by_pointer(st, rd_out_errors,        icmp6stat.icp6s_error);
                rrddim_set_by_pointer(st, rd_in_csum_errors,    icmp6stat.icp6s_checksum);
                rrddim_set_by_pointer(st, rd_in_dest_unreachs,  icmp6stat.icp6s_inhist[ICMP6_DST_UNREACH]);
                rrddim_set_by_pointer(st, rd_in_pkt_too_bigs,   icmp6stat.icp6s_badlen);
                rrddim_set_by_pointer(st, rd_in_time_excds,     icmp6stat.icp6s_inhist[ICMP6_TIME_EXCEEDED]);
                rrddim_set_by_pointer(st, rd_in_parm_problems,  icmp6stat.icp6s_inhist[ICMP6_PARAM_PROB]);
                rrddim_set_by_pointer(st, rd_out_dest_unreachs, icmp6stat.icp6s_outhist[ICMP6_DST_UNREACH]);
                rrddim_set_by_pointer(st, rd_out_time_excds,    icmp6stat.icp6s_outhist[ICMP6_TIME_EXCEEDED]);
                rrddim_set_by_pointer(st, rd_out_parm_problems, icmp6stat.icp6s_outhist[ICMP6_PARAM_PROB]);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (do_icmp6_echos == CONFIG_BOOLEAN_YES || (do_icmp6_echos == CONFIG_BOOLEAN_AUTO && (
                    icmp6stat.icp6s_inhist[ICMP6_ECHO_REQUEST] ||
                    icmp6stat.icp6s_outhist[ICMP6_ECHO_REQUEST] ||
                    icmp6stat.icp6s_inhist[ICMP6_ECHO_REPLY] ||
                    icmp6stat.icp6s_outhist[ICMP6_ECHO_REPLY]))) {
                do_icmp6_echos = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_in = NULL, *rd_out = NULL, *rd_in_replies = NULL, *rd_out_replies = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "icmpechos",
                            NULL,
                            "icmp",
                            NULL,
                            "IPv6 ICMP Echo",
                            "messages/s",
                            "freebsd.plugin",
                            "net.inet6.icmp6.stats",
                            10200,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rd_in          = rrddim_add(st, "InEchos",        NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out         = rrddim_add(st, "OutEchos",       NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_replies  = rrddim_add(st, "InEchoReplies",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_replies = rrddim_add(st, "OutEchoReplies", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_in,          icmp6stat.icp6s_inhist[ICMP6_ECHO_REQUEST]);
                rrddim_set_by_pointer(st, rd_out,         icmp6stat.icp6s_outhist[ICMP6_ECHO_REQUEST]);
                rrddim_set_by_pointer(st, rd_in_replies,  icmp6stat.icp6s_inhist[ICMP6_ECHO_REPLY]);
                rrddim_set_by_pointer(st, rd_out_replies, icmp6stat.icp6s_outhist[ICMP6_ECHO_REPLY]);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (do_icmp6_router == CONFIG_BOOLEAN_YES || (do_icmp6_router == CONFIG_BOOLEAN_AUTO && (
                    icmp6stat.icp6s_inhist[ND_ROUTER_SOLICIT] ||
                    icmp6stat.icp6s_outhist[ND_ROUTER_SOLICIT] ||
                    icmp6stat.icp6s_inhist[ND_ROUTER_ADVERT] ||
                    icmp6stat.icp6s_outhist[ND_ROUTER_ADVERT]))) {
                do_icmp6_router = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_in_solicits = NULL, *rd_out_solicits = NULL,
                              *rd_in_advertisements = NULL, *rd_out_advertisements = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "icmprouter",
                            NULL,
                            "icmp",
                            NULL,
                            "IPv6 Router Messages",
                            "messages/s",
                            "freebsd.plugin",
                            "net.inet6.icmp6.stats",
                            10400,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rd_in_solicits        = rrddim_add(st, "InSolicits",        NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_solicits       = rrddim_add(st, "OutSolicits",       NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_advertisements  = rrddim_add(st, "InAdvertisements",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_advertisements = rrddim_add(st, "OutAdvertisements", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_in_solicits,        icmp6stat.icp6s_inhist[ND_ROUTER_SOLICIT]);
                rrddim_set_by_pointer(st, rd_out_solicits,       icmp6stat.icp6s_outhist[ND_ROUTER_SOLICIT]);
                rrddim_set_by_pointer(st, rd_in_advertisements,  icmp6stat.icp6s_inhist[ND_ROUTER_ADVERT]);
                rrddim_set_by_pointer(st, rd_out_advertisements, icmp6stat.icp6s_outhist[ND_ROUTER_ADVERT]);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (do_icmp6_neighbor == CONFIG_BOOLEAN_YES || (do_icmp6_neighbor == CONFIG_BOOLEAN_AUTO && (
                    icmp6stat.icp6s_inhist[ND_NEIGHBOR_SOLICIT] ||
                    icmp6stat.icp6s_outhist[ND_NEIGHBOR_SOLICIT] ||
                    icmp6stat.icp6s_inhist[ND_NEIGHBOR_ADVERT] ||
                    icmp6stat.icp6s_outhist[ND_NEIGHBOR_ADVERT]))) {
                do_icmp6_neighbor = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_in_solicits = NULL, *rd_out_solicits = NULL,
                              *rd_in_advertisements = NULL, *rd_out_advertisements = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "icmpneighbor",
                            NULL,
                            "icmp",
                            NULL,
                            "IPv6 Neighbor Messages",
                            "messages/s",
                            "freebsd.plugin",
                            "net.inet6.icmp6.stats",
                            10500,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rd_in_solicits        = rrddim_add(st, "InSolicits",        NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_solicits       = rrddim_add(st, "OutSolicits",       NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_advertisements  = rrddim_add(st, "InAdvertisements",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_advertisements = rrddim_add(st, "OutAdvertisements", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_in_solicits,        icmp6stat.icp6s_inhist[ND_NEIGHBOR_SOLICIT]);
                rrddim_set_by_pointer(st, rd_out_solicits,       icmp6stat.icp6s_outhist[ND_NEIGHBOR_SOLICIT]);
                rrddim_set_by_pointer(st, rd_in_advertisements,  icmp6stat.icp6s_inhist[ND_NEIGHBOR_ADVERT]);
                rrddim_set_by_pointer(st, rd_out_advertisements, icmp6stat.icp6s_outhist[ND_NEIGHBOR_ADVERT]);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (do_icmp6_types == CONFIG_BOOLEAN_YES || (do_icmp6_types == CONFIG_BOOLEAN_AUTO && (
                    icmp6stat.icp6s_inhist[1] ||
                    icmp6stat.icp6s_inhist[128] ||
                    icmp6stat.icp6s_inhist[129] ||
                    icmp6stat.icp6s_inhist[136] ||
                    icmp6stat.icp6s_outhist[1] ||
                    icmp6stat.icp6s_outhist[128] ||
                    icmp6stat.icp6s_outhist[129] ||
                    icmp6stat.icp6s_outhist[133] ||
                    icmp6stat.icp6s_outhist[135] ||
                    icmp6stat.icp6s_outhist[136]))) {
                do_icmp6_types = CONFIG_BOOLEAN_YES;

                static RRDSET *st = NULL;
                static RRDDIM *rd_in_1 = NULL, *rd_in_128 = NULL, *rd_in_129 = NULL, *rd_in_136 = NULL,
                              *rd_out_1 = NULL, *rd_out_128 = NULL, *rd_out_129 = NULL, *rd_out_133 = NULL,
                              *rd_out_135 = NULL, *rd_out_143 = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "ipv6",
                            "icmptypes",
                            NULL,
                            "icmp",
                            NULL,
                            "IPv6 ICMP Types",
                            "messages/s",
                            "freebsd.plugin",
                            "net.inet6.icmp6.stats",
                            10700,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rd_in_1    = rrddim_add(st, "InType1",    NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_128  = rrddim_add(st, "InType128",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_129  = rrddim_add(st, "InType129",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_in_136  = rrddim_add(st, "InType136",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_1   = rrddim_add(st, "OutType1",   NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_128 = rrddim_add(st, "OutType128", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_129 = rrddim_add(st, "OutType129", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_133 = rrddim_add(st, "OutType133", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_135 = rrddim_add(st, "OutType135", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_out_143 = rrddim_add(st, "OutType143", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_in_1,    icmp6stat.icp6s_inhist[1]);
                rrddim_set_by_pointer(st, rd_in_128,  icmp6stat.icp6s_inhist[128]);
                rrddim_set_by_pointer(st, rd_in_129,  icmp6stat.icp6s_inhist[129]);
                rrddim_set_by_pointer(st, rd_in_136,  icmp6stat.icp6s_inhist[136]);
                rrddim_set_by_pointer(st, rd_out_1,   icmp6stat.icp6s_outhist[1]);
                rrddim_set_by_pointer(st, rd_out_128, icmp6stat.icp6s_outhist[128]);
                rrddim_set_by_pointer(st, rd_out_129, icmp6stat.icp6s_outhist[129]);
                rrddim_set_by_pointer(st, rd_out_133, icmp6stat.icp6s_outhist[133]);
                rrddim_set_by_pointer(st, rd_out_135, icmp6stat.icp6s_outhist[135]);
                rrddim_set_by_pointer(st, rd_out_143, icmp6stat.icp6s_outhist[143]);
                rrdset_done(st);
            }
        }
    } else {
        error("DISABLED: net.inet6.icmp6.stats module");
        return 1;
    }

    return 0;
}