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
struct TYPE_2__ {scalar_t__ frag_memory; scalar_t__ frag_inuse; scalar_t__ raw_inuse; scalar_t__ udplite_inuse; scalar_t__ udp_mem; scalar_t__ udp_inuse; scalar_t__ tcp_mem; scalar_t__ tcp_alloc; scalar_t__ tcp_tw; scalar_t__ tcp_orphan; scalar_t__ tcp_inuse; scalar_t__ sockets_used; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;
typedef  int /*<<< orphan*/  ARL_BASE ;

/* Variables and functions */
 int CONFIG_BOOLEAN_AUTO ; 
 int CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV4_FRAGMENTS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV4_FRAGMENTS_MEM ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV4_RAW ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV4_SOCKETS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV4_TCP_MEM ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV4_TCP_SOCKETS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV4_UDP ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV4_UDPLITE ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPV4_UDP_MEM ; 
 int /*<<< orphan*/  PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME ; 
 int /*<<< orphan*/  PLUGIN_PROC_NAME ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  arl_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arl_callback_str2kernel_uint_t ; 
 scalar_t__ arl_check (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * arl_create (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arl_expect (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  config_get (char*,char*,char*) ; 
 int config_get_boolean_ondemand (char*,char*,int) ; 
 long long config_get_number (char*,char*,long long) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 size_t procfile_lines (int /*<<< orphan*/ *) ; 
 char* procfile_lineword (int /*<<< orphan*/ *,size_t,size_t) ; 
 size_t procfile_linewords (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * procfile_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_tcp_max_orphans () ; 
 int /*<<< orphan*/  read_tcp_mem () ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ simple_hash (char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ sockstat_root ; 
 scalar_t__ strcmp (char*,char*) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int do_proc_net_sockstat(int update_every, usec_t dt) {
    (void)dt;

    static procfile *ff = NULL;

    static uint32_t hash_sockets = 0,
                    hash_raw = 0,
                    hash_frag = 0,
                    hash_tcp = 0,
                    hash_udp = 0,
                    hash_udplite = 0;

    static long long update_constants_every = 60, update_constants_count = 0;

    static ARL_BASE *arl_sockets = NULL;
    static ARL_BASE *arl_tcp = NULL;
    static ARL_BASE *arl_udp = NULL;
    static ARL_BASE *arl_udplite = NULL;
    static ARL_BASE *arl_raw = NULL;
    static ARL_BASE *arl_frag = NULL;

    static int do_sockets = -1, do_tcp_sockets = -1, do_tcp_mem = -1, do_udp_sockets = -1, do_udp_mem = -1, do_udplite_sockets = -1, do_raw_sockets = -1, do_frag_sockets = -1, do_frag_mem = -1;

    static char     *keys[7]  = { NULL };
    static uint32_t hashes[7] = { 0 };
    static ARL_BASE *bases[7] = { NULL };

    if(unlikely(!arl_sockets)) {
        do_sockets         = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat", "ipv4 sockets", CONFIG_BOOLEAN_AUTO);
        do_tcp_sockets     = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat", "ipv4 TCP sockets", CONFIG_BOOLEAN_AUTO);
        do_tcp_mem         = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat", "ipv4 TCP memory", CONFIG_BOOLEAN_AUTO);
        do_udp_sockets     = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat", "ipv4 UDP sockets", CONFIG_BOOLEAN_AUTO);
        do_udp_mem         = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat", "ipv4 UDP memory", CONFIG_BOOLEAN_AUTO);
        do_udplite_sockets = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat", "ipv4 UDPLITE sockets", CONFIG_BOOLEAN_AUTO);
        do_raw_sockets     = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat", "ipv4 RAW sockets", CONFIG_BOOLEAN_AUTO);
        do_frag_sockets    = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat", "ipv4 FRAG sockets", CONFIG_BOOLEAN_AUTO);
        do_frag_mem        = config_get_boolean_ondemand("plugin:proc:/proc/net/sockstat", "ipv4 FRAG memory", CONFIG_BOOLEAN_AUTO);

        update_constants_every = config_get_number("plugin:proc:/proc/net/sockstat", "update constants every", update_constants_every);
        update_constants_count = update_constants_every;

        arl_sockets = arl_create("sockstat/sockets", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_sockets, "used", &sockstat_root.sockets_used);

        arl_tcp = arl_create("sockstat/TCP", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_tcp, "inuse",  &sockstat_root.tcp_inuse);
        arl_expect(arl_tcp, "orphan", &sockstat_root.tcp_orphan);
        arl_expect(arl_tcp, "tw",     &sockstat_root.tcp_tw);
        arl_expect(arl_tcp, "alloc",  &sockstat_root.tcp_alloc);
        arl_expect(arl_tcp, "mem",    &sockstat_root.tcp_mem);

        arl_udp = arl_create("sockstat/UDP", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_udp, "inuse", &sockstat_root.udp_inuse);
        arl_expect(arl_udp, "mem", &sockstat_root.udp_mem);

        arl_udplite = arl_create("sockstat/UDPLITE", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_udplite, "inuse", &sockstat_root.udplite_inuse);

        arl_raw = arl_create("sockstat/RAW", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_raw, "inuse", &sockstat_root.raw_inuse);

        arl_frag = arl_create("sockstat/FRAG", arl_callback_str2kernel_uint_t, 60);
        arl_expect(arl_frag, "inuse", &sockstat_root.frag_inuse);
        arl_expect(arl_frag, "memory", &sockstat_root.frag_memory);

        hash_sockets = simple_hash("sockets");
        hash_tcp = simple_hash("TCP");
        hash_udp = simple_hash("UDP");
        hash_udplite = simple_hash("UDPLITE");
        hash_raw = simple_hash("RAW");
        hash_frag = simple_hash("FRAG");

        keys[0] = "sockets"; hashes[0] = hash_sockets; bases[0] = arl_sockets;
        keys[1] = "TCP";     hashes[1] = hash_tcp;     bases[1] = arl_tcp;
        keys[2] = "UDP";     hashes[2] = hash_udp;     bases[2] = arl_udp;
        keys[3] = "UDPLITE"; hashes[3] = hash_udplite; bases[3] = arl_udplite;
        keys[4] = "RAW";     hashes[4] = hash_raw;     bases[4] = arl_raw;
        keys[5] = "FRAG";    hashes[5] = hash_frag;    bases[5] = arl_frag;
        keys[6] = NULL; // terminator
    }

    update_constants_count += update_every;
    if(unlikely(update_constants_count > update_constants_every)) {
        read_tcp_max_orphans();
        read_tcp_mem();
        update_constants_count = 0;
    }

    if(unlikely(!ff)) {
        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/proc/net/sockstat");
        ff = procfile_open(config_get("plugin:proc:/proc/net/sockstat", "filename to monitor", filename), " \t:", PROCFILE_FLAG_DEFAULT);
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

    if(do_sockets == CONFIG_BOOLEAN_YES || (do_sockets == CONFIG_BOOLEAN_AUTO && sockstat_root.sockets_used)) {
        do_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_used = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4"
                    , "sockstat_sockets"
                    , NULL
                    , "sockets"
                    , NULL
                    , "IPv4 Sockets Used"
                    , "sockets"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME
                    , NETDATA_CHART_PRIO_IPV4_SOCKETS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_used = rrddim_add(st, "used", NULL,  1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_used, (collected_number)sockstat_root.sockets_used);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_tcp_sockets == CONFIG_BOOLEAN_YES || (do_tcp_sockets == CONFIG_BOOLEAN_AUTO && (sockstat_root.tcp_inuse || sockstat_root.tcp_orphan || sockstat_root.tcp_tw || sockstat_root.tcp_alloc))) {
        do_tcp_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL,
                      *rd_orphan = NULL,
                      *rd_timewait = NULL,
                      *rd_alloc = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4"
                    , "sockstat_tcp_sockets"
                    , NULL
                    , "tcp"
                    , NULL
                    , "IPv4 TCP Sockets"
                    , "sockets"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME
                    , NETDATA_CHART_PRIO_IPV4_TCP_SOCKETS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_alloc    = rrddim_add(st, "alloc",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
            rd_orphan   = rrddim_add(st, "orphan",    NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
            rd_timewait = rrddim_add(st, "timewait",  NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat_root.tcp_inuse);
        rrddim_set_by_pointer(st, rd_orphan,   (collected_number)sockstat_root.tcp_orphan);
        rrddim_set_by_pointer(st, rd_timewait, (collected_number)sockstat_root.tcp_tw);
        rrddim_set_by_pointer(st, rd_alloc,    (collected_number)sockstat_root.tcp_alloc);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_tcp_mem == CONFIG_BOOLEAN_YES || (do_tcp_mem == CONFIG_BOOLEAN_AUTO && sockstat_root.tcp_mem)) {
        do_tcp_mem = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_mem = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4"
                    , "sockstat_tcp_mem"
                    , NULL
                    , "tcp"
                    , NULL
                    , "IPv4 TCP Sockets Memory"
                    , "KiB"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME
                    , NETDATA_CHART_PRIO_IPV4_TCP_MEM
                    , update_every
                    , RRDSET_TYPE_AREA
            );

            rd_mem = rrddim_add(st, "mem", NULL, sysconf(_SC_PAGESIZE), 1024, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_mem, (collected_number)sockstat_root.tcp_mem);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_udp_sockets == CONFIG_BOOLEAN_YES || (do_udp_sockets == CONFIG_BOOLEAN_AUTO && sockstat_root.udp_inuse)) {
        do_udp_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4"
                    , "sockstat_udp_sockets"
                    , NULL
                    , "udp"
                    , NULL
                    , "IPv4 UDP Sockets"
                    , "sockets"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME
                    , NETDATA_CHART_PRIO_IPV4_UDP
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat_root.udp_inuse);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_udp_mem == CONFIG_BOOLEAN_YES || (do_udp_mem == CONFIG_BOOLEAN_AUTO && sockstat_root.udp_mem)) {
        do_udp_mem = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_mem = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4"
                    , "sockstat_udp_mem"
                    , NULL
                    , "udp"
                    , NULL
                    , "IPv4 UDP Sockets Memory"
                    , "KiB"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME
                    , NETDATA_CHART_PRIO_IPV4_UDP_MEM
                    , update_every
                    , RRDSET_TYPE_AREA
            );

            rd_mem = rrddim_add(st, "mem", NULL, sysconf(_SC_PAGESIZE), 1024, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_mem, (collected_number)sockstat_root.udp_mem);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_udplite_sockets == CONFIG_BOOLEAN_YES || (do_udplite_sockets == CONFIG_BOOLEAN_AUTO && sockstat_root.udplite_inuse)) {
        do_udplite_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4"
                    , "sockstat_udplite_sockets"
                    , NULL
                    , "udplite"
                    , NULL
                    , "IPv4 UDPLITE Sockets"
                    , "sockets"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME
                    , NETDATA_CHART_PRIO_IPV4_UDPLITE
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat_root.udplite_inuse);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_raw_sockets == CONFIG_BOOLEAN_YES || (do_raw_sockets == CONFIG_BOOLEAN_AUTO && sockstat_root.raw_inuse)) {
        do_raw_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4"
                    , "sockstat_raw_sockets"
                    , NULL
                    , "raw"
                    , NULL
                    , "IPv4 RAW Sockets"
                    , "sockets"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME
                    , NETDATA_CHART_PRIO_IPV4_RAW
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat_root.raw_inuse);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_frag_sockets == CONFIG_BOOLEAN_YES || (do_frag_sockets == CONFIG_BOOLEAN_AUTO && sockstat_root.frag_inuse)) {
        do_frag_sockets = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_inuse = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4"
                    , "sockstat_frag_sockets"
                    , NULL
                    , "fragments"
                    , NULL
                    , "IPv4 FRAG Sockets"
                    , "fragments"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME
                    , NETDATA_CHART_PRIO_IPV4_FRAGMENTS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_inuse    = rrddim_add(st, "inuse",     NULL,   1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_inuse,    (collected_number)sockstat_root.frag_inuse);
        rrdset_done(st);
    }

    // ------------------------------------------------------------------------

    if(do_frag_mem == CONFIG_BOOLEAN_YES || (do_frag_mem == CONFIG_BOOLEAN_AUTO && sockstat_root.frag_memory)) {
        do_frag_mem = CONFIG_BOOLEAN_YES;

        static RRDSET *st = NULL;
        static RRDDIM *rd_mem = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4"
                    , "sockstat_frag_mem"
                    , NULL
                    , "fragments"
                    , NULL
                    , "IPv4 FRAG Sockets Memory"
                    , "KiB"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_SOCKSTAT_NAME
                    , NETDATA_CHART_PRIO_IPV4_FRAGMENTS_MEM
                    , update_every
                    , RRDSET_TYPE_AREA
            );

            rd_mem = rrddim_add(st, "mem", NULL, 1, 1024, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_mem, (collected_number)sockstat_root.frag_memory);
        rrdset_done(st);
    }

    return 0;
}