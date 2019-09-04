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
typedef  int /*<<< orphan*/  procfile ;
typedef  int /*<<< orphan*/  RRDSET ;

/* Variables and functions */
 int BITS_IN_A_KILOBIT ; 
 int /*<<< orphan*/  CONFIG_SECTION_PLUGIN_PROC_NET_IPVS ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPVS_NET ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPVS_PACKETS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_IPVS_SOCKETS ; 
 int /*<<< orphan*/  PLUGIN_PROC_MODULE_NET_IPVS_NAME ; 
 int /*<<< orphan*/  PLUGIN_PROC_NAME ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  RRD_TYPE_NET_IPVS ; 
 int /*<<< orphan*/  config_get (int /*<<< orphan*/ ,char*,char*) ; 
 int config_get_boolean (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 int procfile_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfile_lineword (int /*<<< orphan*/ *,int,int) ; 
 int procfile_linewords (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * procfile_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 unsigned long long strtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

int do_proc_net_ip_vs_stats(int update_every, usec_t dt) {
    (void)dt;
    static int do_bandwidth = -1, do_sockets = -1, do_packets = -1;
    static procfile *ff = NULL;

    if(do_bandwidth == -1)  do_bandwidth    = config_get_boolean(CONFIG_SECTION_PLUGIN_PROC_NET_IPVS, "IPVS bandwidth", 1);
    if(do_sockets == -1)    do_sockets      = config_get_boolean(CONFIG_SECTION_PLUGIN_PROC_NET_IPVS, "IPVS connections", 1);
    if(do_packets == -1)    do_packets      = config_get_boolean(CONFIG_SECTION_PLUGIN_PROC_NET_IPVS, "IPVS packets", 1);

    if(!ff) {
        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/proc/net/ip_vs_stats");
        ff = procfile_open(config_get(CONFIG_SECTION_PLUGIN_PROC_NET_IPVS, "filename to monitor", filename), " \t,:|", PROCFILE_FLAG_DEFAULT);
    }
    if(!ff) return 1;

    ff = procfile_readall(ff);
    if(!ff) return 0; // we return 0, so that we will retry to open it next time

    // make sure we have 3 lines
    if(procfile_lines(ff) < 3) return 1;

    // make sure we have 5 words on the 3rd line
    if(procfile_linewords(ff, 2) < 5) return 1;

    unsigned long long entries, InPackets, OutPackets, InBytes, OutBytes;

    entries     = strtoull(procfile_lineword(ff, 2, 0), NULL, 16);
    InPackets   = strtoull(procfile_lineword(ff, 2, 1), NULL, 16);
    OutPackets  = strtoull(procfile_lineword(ff, 2, 2), NULL, 16);
    InBytes     = strtoull(procfile_lineword(ff, 2, 3), NULL, 16);
    OutBytes    = strtoull(procfile_lineword(ff, 2, 4), NULL, 16);


    // --------------------------------------------------------------------

    if(do_sockets) {
        static RRDSET *st = NULL;

        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    RRD_TYPE_NET_IPVS
                    , "sockets"
                    , NULL
                    , RRD_TYPE_NET_IPVS
                    , NULL
                    , "IPVS New Connections"
                    , "connections/s"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_IPVS_NAME
                    , NETDATA_CHART_PRIO_IPVS_SOCKETS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rrddim_add(st, "connections", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else rrdset_next(st);

        rrddim_set(st, "connections", entries);
        rrdset_done(st);
    }

    // --------------------------------------------------------------------

    if(do_packets) {
        static RRDSET *st = NULL;
        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    RRD_TYPE_NET_IPVS
                    , "packets"
                    , NULL
                    , RRD_TYPE_NET_IPVS
                    , NULL
                    , "IPVS Packets"
                    , "packets/s"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_IPVS_NAME
                    , NETDATA_CHART_PRIO_IPVS_PACKETS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rrddim_add(st, "received", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rrddim_add(st, "sent", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else rrdset_next(st);

        rrddim_set(st, "received", InPackets);
        rrddim_set(st, "sent", OutPackets);
        rrdset_done(st);
    }

    // --------------------------------------------------------------------

    if(do_bandwidth) {
        static RRDSET *st = NULL;
        if(unlikely(!st)) {
            st = rrdset_create_localhost(
                    RRD_TYPE_NET_IPVS
                    , "net"
                    , NULL
                    , RRD_TYPE_NET_IPVS
                    , NULL
                    , "IPVS Bandwidth"
                    , "kilobits/s"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_NET_IPVS_NAME
                    , NETDATA_CHART_PRIO_IPVS_NET
                    , update_every
                    , RRDSET_TYPE_AREA
            );

            rrddim_add(st, "received", NULL, 8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
            rrddim_add(st, "sent", NULL,    -8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
        }
        else rrdset_next(st);

        rrddim_set(st, "received", InBytes);
        rrddim_set(st, "sent", OutBytes);
        rrdset_done(st);
    }

    return 0;
}