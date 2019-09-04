#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  procfile ;
typedef  int /*<<< orphan*/  collected_number ;
struct TYPE_2__ {scalar_t__ frag6_inuse; scalar_t__ raw6_inuse; scalar_t__ udplite6_inuse; scalar_t__ udp6_inuse; scalar_t__ tcp6_inuse; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;
typedef  int /*<<< orphan*/  ARL_BASE ;

/* Variables and functions */
 int CONFIG_BOOLEAN_AUTO ; 
 int CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV6_FRAGMENTS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV6_RAW ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV6_TCP ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV6_UDP ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV6_UDPLITE ; 
 int /*<<< orphan*/  PLUGIN_PROC_MODULE_NET_SOCKSTAT6_NAME ; 
 int /*<<< orphan*/  PLUGIN_PROC_NAME ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  arl_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arl_callback_str2kernel_uint_t ; 
 scalar_t__ arl_check (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * arl_create (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arl_expect (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  config_get (char*,char*,char*) ; 
 int config_get_boolean_ondemand (char*,char*,int) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 size_t procfile_lines (int /*<<< orphan*/ *) ; 
 char* procfile_lineword (int /*<<< orphan*/ *,size_t,size_t) ; 
 size_t procfile_linewords (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * procfile_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ simple_hash (char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ sockstat6_root ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ unlikely (int) ; 

int do_proc_net_sockstat6(int update_every, usec_t dt) {
    (void)dt;

    static procfile *ff = NULL;

    static uint32_t hash_raw = 0,
                    hash_frag = 0,
                    hash_tcp = 0,
                    hash_udp = 0,
                    hash_udplite = 0;

    static ARL_BASE *arl_tcp = NULL;
    static ARL_BASE *arl_udp = NULL;
    static ARL_BASE *arl_udplite = NULL;
    static ARL_BASE *arl_raw = NULL;
    static ARL_BASE *arl_frag = NULL;

    static int do_tcp_sockets = -1, do_udp_sockets = -1, do_udplite_sockets = -1, do_raw_sockets = -1, do_frag_sockets = -1;

    static char     *keys[6]  = { NULL };
    static uint32_t hashes[6] = { 0 };
    static ARL_BASE *bases[6] = { NULL };

    if(unlikely(!arl_tcp)) {
        do_tcp_sockets     = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat6", "ipv6 TCP sockets", CONFIG_BOOLEAN_AUTO);
        do_udp_sockets     = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat6", "ipv6 UDP sockets", CONFIG_BOOLEAN_AUTO);
        do_udplite_sockets = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat6", "ipv6 UDPLITE sockets", CONFIG_BOOLEAN_AUTO);
        do_raw_sockets     = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat6", "ipv6 RAW sockets", CONFIG_BOOLEAN_AUTO);
        do_frag_sockets    = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat6", "ipv6 FRAG sockets", CONFIG_BOOLEAN_AUTO);

        arl_tcp = arl_create("sockstat6/TCP6", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_tcp, "inuse",  &sockstat6_root.tcp6_inuse);

        arl_udp = arl_create("sockstat6/UDP6", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_udp, "inuse", &sockstat6_root.udp6_inuse);

        arl_udplite = arl_create("sockstat6/UDPLITE6", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_udplite, "inuse", &sockstat6_root.udplite6_inuse);

        arl_raw = arl_create("sockstat6/RAW6", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_raw, "inuse", &sockstat6_root.raw6_inuse);

        arl_frag = arl_create("sockstat6/FRAG6", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_frag, "inuse", &sockstat6_root.frag6_inuse);

        hash_tcp = simple_hash("TCP6");
        hash_udp = simple_hash("UDP6");
        hash_udplite = simple_hash("UDPLITE6");
        hash_raw = simple_hash("RAW6");
        hash_frag = simple_hash("FRAG6");

        keys[0] = "TCP6";     hashes[0] = hash_tcp;     bases[0] = arl_tcp;
        keys[1] = "UDP6";     hashes[1] = hash_udp;     bases[1] = arl_udp;
        keys[2] = "UDPLITE6"; hashes[2] = hash_udplite; bases[2] = arl_udplite;
        keys[3] = "RAW6";     hashes[3] = hash_raw;     bases[3] = arl_raw;
        keys[4] = "FRAG6";    hashes[4] = hash_frag;    bases[4] = arl_frag;
        keys[5] = NULL; // terminator
    }

    if(unlikely(!ff)) {
        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/proc/net/sockstat6");
        ff = procfile_open(config_get("plugin:proc:/proc/net/sockstat6", "filename to monitor", filename), " \t:", PROCFILE_FLAG_DEFAULT);
        if(unlikely(!ff)) return 1;
    }

    ff = procfile_readall(ff);
    if(unlikely(!ff)) return 0; // we return 0, so that we will retry to open it next time

    size_t lines = procfile_lines(ff), l;

    for(l = 0; l < lines ;l++) {
        size_t  words = procfile_linewords(ff, l);
        char     *key = procfile_lineword(ff, l, 0);
        uint32_t hash = simple_hash(key);

        int k;
        for(k = 0; keys[k] ; k++) {
            if(unlikely(hash == hashes[k] && strcmp(key, keys[k]) == 0)) {
                // fprintf(stderr, "KEY: '%s', l=%zu, w=1, words=%zu\n", key, l, words);
                ARL_BASE *arl = bases[k];
                arl_begin(arl);
                size_t w = 1;

                while(w + 1 < words) {
                    char *name  = procfile_lineword(ff, l, w); w++;
                    char *value = procfile_lineword(ff, l, w); w++;
                    // fprintf(stderr, " > NAME '%s', VALUE '%s', l=%zu, w=%zu, words=%zu\n", name, value, l, w, words);
                    if(unlikely(arl_check(arl, name, value) != 0))
                        break;
                }

                break;
            }
        }
    }

    // ------------------------------------------------------------------------

    if(do_tcp_sockets == CONFIG_BOOLEAN_YES || (do_tcp_sockets == CONFIG_BOOLEAN_AUTO && (sockstat6_root.tcp6_inuse))) {
        do_tcp_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv6"
                    , "sockstat6_tcp_sockets"
                    , NULL
                    , "tcp6"
                    , NULL
                    , "IPv6 TCP Sockets"
                    , "sockets"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT6_NAME
                    , NETDATA_CHART_PRIO_IPV6_TCP
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat6_root.tcp6_inuse);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_udp_sockets == CONFIG_BOOLEAN_YES || (do_udp_sockets == CONFIG_BOOLEAN_AUTO && sockstat6_root.udp6_inuse)) {
        do_udp_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv6"
                    , "sockstat6_udp_sockets"
                    , NULL
                    , "udp6"
                    , NULL
                    , "IPv6 UDP Sockets"
                    , "sockets"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT6_NAME
                    , NETDATA_CHART_PRIO_IPV6_UDP
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat6_root.udp6_inuse);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_udplite_sockets == CONFIG_BOOLEAN_YES || (do_udplite_sockets == CONFIG_BOOLEAN_AUTO && sockstat6_root.udplite6_inuse)) {
        do_udplite_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv6"
                    , "sockstat6_udplite_sockets"
                    , NULL
                    , "udplite6"
                    , NULL
                    , "IPv6 UDPLITE Sockets"
                    , "sockets"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT6_NAME
                    , NETDATA_CHART_PRIO_IPV6_UDPLITE
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat6_root.udplite6_inuse);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_raw_sockets == CONFIG_BOOLEAN_YES || (do_raw_sockets == CONFIG_BOOLEAN_AUTO && sockstat6_root.raw6_inuse)) {
        do_raw_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv6"
                    , "sockstat6_raw_sockets"
                    , NULL
                    , "raw6"
                    , NULL
                    , "IPv6 RAW Sockets"
                    , "sockets"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT6_NAME
                    , NETDATA_CHART_PRIO_IPV6_RAW
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat6_root.raw6_inuse);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_frag_sockets == CONFIG_BOOLEAN_YES || (do_frag_sockets == CONFIG_BOOLEAN_AUTO && sockstat6_root.frag6_inuse)) {
        do_frag_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv6"
                    , "sockstat6_frag_sockets"
                    , NULL
                    , "fragments6"
                    , NULL
                    , "IPv6 FRAG Sockets"
                    , "fragments"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT6_NAME
                    , NETDATA_CHART_PRIO_IPV6_FRAGMENTS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat6_root.frag6_inuse);
        rrdset_done(st);
    }

    return 0;
}