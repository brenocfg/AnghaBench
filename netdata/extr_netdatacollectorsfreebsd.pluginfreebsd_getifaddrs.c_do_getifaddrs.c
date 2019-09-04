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
typedef  scalar_t__ u_long ;
struct ifaddrs {char* ifa_name; scalar_t__ ifa_data; TYPE_1__* ifa_addr; struct ifaddrs* ifa_next; } ;
struct if_data {scalar_t__ ifi_collisions; scalar_t__ ifi_iqdrops; scalar_t__ ifi_oerrors; scalar_t__ ifi_ierrors; scalar_t__ ifi_omcasts; scalar_t__ ifi_imcasts; scalar_t__ ifi_opackets; scalar_t__ ifi_ipackets; scalar_t__ ifi_obytes; scalar_t__ ifi_ibytes; } ;
struct cgroup_network_interface {int updated; int configured; int enabled; scalar_t__ do_bandwidth; scalar_t__ do_packets; scalar_t__ do_errors; scalar_t__ do_drops; scalar_t__ do_events; int /*<<< orphan*/ * st_events; int /*<<< orphan*/ * rd_events_coll; int /*<<< orphan*/ * st_drops; int /*<<< orphan*/ * rd_drops_in; int /*<<< orphan*/ * st_errors; int /*<<< orphan*/ * rd_errors_out; int /*<<< orphan*/ * rd_errors_in; int /*<<< orphan*/ * st_packets; int /*<<< orphan*/ * rd_packets_m_out; int /*<<< orphan*/ * rd_packets_m_in; int /*<<< orphan*/ * rd_packets_out; int /*<<< orphan*/ * rd_packets_in; int /*<<< orphan*/ * st_bandwidth; int /*<<< orphan*/ * rd_bandwidth_out; int /*<<< orphan*/ * rd_bandwidth_in; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  SIMPLE_PATTERN ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_LINK ; 
 int BITS_IN_A_KILOBIT ; 
 scalar_t__ CONFIG_BOOLEAN_AUTO ; 
 int CONFIG_BOOLEAN_NO ; 
 scalar_t__ CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_FIRST_NET_DROPS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_FIRST_NET_ERRORS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_FIRST_NET_EVENTS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_FIRST_NET_IFACE ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_FIRST_NET_PACKETS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_IPV4 ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_IPV6 ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_NET ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_PACKETS ; 
 int /*<<< orphan*/  RRDSET_FLAG_DETAIL ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  SIMPLE_PATTERN_EXACT ; 
 int /*<<< orphan*/  config_get (char*,char*,char*) ; 
 void* config_get_boolean_ondemand (char*,char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 struct cgroup_network_interface* get_network_interface (char*) ; 
 int getifaddrs (struct ifaddrs**) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  network_interfaces_cleanup () ; 
 scalar_t__ network_interfaces_found ; 
 void* rrddim_add (int /*<<< orphan*/ *,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 void* rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simple_pattern_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_pattern_matches (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char*,char*) ; 
 scalar_t__ unlikely (int) ; 

int do_getifaddrs(int update_every, usec_t dt) {
    (void)dt;

#define DEFAULT_EXLUDED_INTERFACES "lo*"
#define DEFAULT_PHYSICAL_INTERFACES "igb* ix* cxl* em* ixl* ixlv* bge* ixgbe* vtnet*"
#define CONFIG_SECTION_GETIFADDRS "plugin:freebsd:getifaddrs"

    static int enable_new_interfaces = -1;
    static int do_bandwidth_ipv4 = -1, do_bandwidth_ipv6 = -1, do_bandwidth = -1, do_packets = -1, do_bandwidth_net = -1, do_packets_net = -1,
            do_errors = -1, do_drops = -1, do_events = -1;
    static SIMPLE_PATTERN *excluded_interfaces = NULL, *physical_interfaces = NULL;

    if (unlikely(enable_new_interfaces == -1)) {
        enable_new_interfaces = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS,
                                                              "enable new interfaces detected at runtime",
                                                              CONFIG_BOOLEAN_AUTO);

        do_bandwidth_net  = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS, "total bandwidth for physical interfaces",
                                                       CONFIG_BOOLEAN_AUTO);
        do_packets_net    = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS, "total packets for physical interfaces",
                                                       CONFIG_BOOLEAN_AUTO);
        do_bandwidth_ipv4 = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS, "total bandwidth for ipv4 interfaces",
                                                        CONFIG_BOOLEAN_AUTO);
        do_bandwidth_ipv6 = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS, "total bandwidth for ipv6 interfaces",
                                                        CONFIG_BOOLEAN_AUTO);
        do_bandwidth      = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS, "bandwidth for all interfaces",
                                                        CONFIG_BOOLEAN_AUTO);
        do_packets        = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS, "packets for all interfaces",
                                                        CONFIG_BOOLEAN_AUTO);
        do_errors         = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS, "errors for all interfaces",
                                                        CONFIG_BOOLEAN_AUTO);
        do_drops          = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS, "drops for all interfaces",
                                                        CONFIG_BOOLEAN_AUTO);
        do_events         = config_get_boolean_ondemand(CONFIG_SECTION_GETIFADDRS, "collisions for all interfaces",
                                                        CONFIG_BOOLEAN_AUTO);

        excluded_interfaces = simple_pattern_create(
                config_get(CONFIG_SECTION_GETIFADDRS, "disable by default interfaces matching", DEFAULT_EXLUDED_INTERFACES)
                , NULL
                , SIMPLE_PATTERN_EXACT
        );
        physical_interfaces = simple_pattern_create(
                config_get(CONFIG_SECTION_GETIFADDRS, "set physical interfaces for system.net", DEFAULT_PHYSICAL_INTERFACES)
                , NULL
                , SIMPLE_PATTERN_EXACT
        );
    }

    if (likely(do_bandwidth_ipv4 || do_bandwidth_ipv6 || do_bandwidth || do_packets || do_errors || do_bandwidth_net || do_packets_net ||
               do_drops || do_events)) {
        struct ifaddrs *ifap;

        if (unlikely(getifaddrs(&ifap))) {
            error("FREEBSD: getifaddrs() failed");
            do_bandwidth_net = 0;
            error("DISABLED: system.net chart");
            do_packets_net = 0;
            error("DISABLED: system.packets chart");
            do_bandwidth_ipv4 = 0;
            error("DISABLED: system.ipv4 chart");
            do_bandwidth_ipv6 = 0;
            error("DISABLED: system.ipv6 chart");
            do_bandwidth = 0;
            error("DISABLED: net.* charts");
            do_packets = 0;
            error("DISABLED: net_packets.* charts");
            do_errors = 0;
            error("DISABLED: net_errors.* charts");
            do_drops = 0;
            error("DISABLED: net_drops.* charts");
            do_events = 0;
            error("DISABLED: net_events.* charts");
            error("DISABLED: getifaddrs module");
            return 1;
        } else {
#define IFA_DATA(s) (((struct if_data *)ifa->ifa_data)->ifi_ ## s)
            struct ifaddrs *ifa;
            struct iftot {
                u_long  ift_ibytes;
                u_long  ift_obytes;
                u_long  ift_ipackets;
                u_long  ift_opackets;
                u_long  ift_imcasts;
                u_long  ift_omcasts;
            } iftot = {0, 0, 0, 0, 0, 0};

            // --------------------------------------------------------------------

            if (likely(do_bandwidth_net)) {

                iftot.ift_ibytes = iftot.ift_obytes = 0;
                for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
                    if (ifa->ifa_addr->sa_family != AF_LINK)
                        continue;
                    if (!simple_pattern_matches(physical_interfaces, ifa->ifa_name))
                        continue;
                    iftot.ift_ibytes += IFA_DATA(ibytes);
                    iftot.ift_obytes += IFA_DATA(obytes);
                }

                static RRDSET *st = NULL;
                static RRDDIM *rd_in = NULL, *rd_out = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost("system",
                                                 "net",
                                                 NULL,
                                                 "network",
                                                 NULL,
                                                 "Network Traffic",
                                                 "kilobits/s",
                                                 "freebsd.plugin",
                                                 "getifaddrs",
                                                 NETDATA_CHART_PRIO_SYSTEM_NET,
                                                 update_every,
                                                 RRDSET_TYPE_AREA
                                                 );

                    rd_in  = rrddim_add(st, "InOctets",  "received", 8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
                    rd_out = rrddim_add(st, "OutOctets", "sent",    -8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_in,  iftot.ift_ibytes);
                rrddim_set_by_pointer(st, rd_out, iftot.ift_obytes);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (likely(do_packets_net)) {

                iftot.ift_ipackets = iftot.ift_opackets = iftot.ift_imcasts = iftot.ift_omcasts = 0;
                for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
                    if (ifa->ifa_addr->sa_family != AF_LINK)
                        continue;
                    if (!simple_pattern_matches(physical_interfaces, ifa->ifa_name))
                        continue;
                    iftot.ift_ipackets += IFA_DATA(ipackets);
                    iftot.ift_opackets += IFA_DATA(opackets);
                    iftot.ift_imcasts += IFA_DATA(imcasts);
                    iftot.ift_omcasts += IFA_DATA(omcasts);
                }

                static RRDSET *st = NULL;
                static RRDDIM *rd_packets_in = NULL, *rd_packets_out = NULL, *rd_packets_m_in = NULL, *rd_packets_m_out = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost("system",
                                                 "packets",
                                                 NULL,
                                                 "network",
                                                 NULL,
                                                 "Network Packets",
                                                 "packets/s",
                                                 "freebsd.plugin",
                                                 "getifaddrs",
                                                 NETDATA_CHART_PRIO_SYSTEM_PACKETS,
                                                 update_every,
                                                 RRDSET_TYPE_LINE
                                                 );

                    rrdset_flag_set(st, RRDSET_FLAG_DETAIL);

                    rd_packets_in    = rrddim_add(st, "received",           NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_packets_out   = rrddim_add(st, "sent",               NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_packets_m_in  = rrddim_add(st, "multicast_received", NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rd_packets_m_out = rrddim_add(st, "multicast_sent",     NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_packets_in,    iftot.ift_ipackets);
                rrddim_set_by_pointer(st, rd_packets_out,   iftot.ift_opackets);
                rrddim_set_by_pointer(st, rd_packets_m_in,  iftot.ift_imcasts);
                rrddim_set_by_pointer(st, rd_packets_m_out, iftot.ift_omcasts);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (likely(do_bandwidth_ipv4)) {
                iftot.ift_ibytes = iftot.ift_obytes = 0;
                for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
                    if (ifa->ifa_addr->sa_family != AF_INET)
                        continue;
                    iftot.ift_ibytes += IFA_DATA(ibytes);
                    iftot.ift_obytes += IFA_DATA(obytes);
                }

                static RRDSET *st = NULL;
                static RRDDIM *rd_in = NULL, *rd_out = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost("system",
                                                 "ipv4",
                                                 NULL,
                                                 "network",
                                                 NULL,
                                                 "IPv4 Bandwidth",
                                                 "kilobits/s",
                                                 "freebsd.plugin",
                                                 "getifaddrs",
                                                 NETDATA_CHART_PRIO_SYSTEM_IPV4,
                                                 update_every,
                                                 RRDSET_TYPE_AREA
                    );

                    rd_in  = rrddim_add(st, "InOctets",  "received", 8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
                    rd_out = rrddim_add(st, "OutOctets", "sent",    -8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_in,  iftot.ift_ibytes);
                rrddim_set_by_pointer(st, rd_out, iftot.ift_obytes);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (likely(do_bandwidth_ipv6)) {
                iftot.ift_ibytes = iftot.ift_obytes = 0;
                for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
                    if (ifa->ifa_addr->sa_family != AF_INET6)
                        continue;
                    iftot.ift_ibytes += IFA_DATA(ibytes);
                    iftot.ift_obytes += IFA_DATA(obytes);
                }

                static RRDSET *st = NULL;
                static RRDDIM *rd_in = NULL, *rd_out = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost("system",
                                                 "ipv6",
                                                 NULL,
                                                 "network",
                                                 NULL,
                                                 "IPv6 Bandwidth",
                                                 "kilobits/s",
                                                 "freebsd.plugin",
                                                 "getifaddrs",
                                                 NETDATA_CHART_PRIO_SYSTEM_IPV6,
                                                 update_every,
                                                 RRDSET_TYPE_AREA
                    );

                    rd_in  = rrddim_add(st, "received", NULL,  8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
                    rd_out = rrddim_add(st, "sent",     NULL, -8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
                } else
                    rrdset_next(st);

                rrddim_set_by_pointer(st, rd_in,  iftot.ift_ibytes);
                rrddim_set_by_pointer(st, rd_out, iftot.ift_obytes);
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            network_interfaces_found = 0;

            for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
                if (ifa->ifa_addr->sa_family != AF_LINK)
                    continue;

                struct cgroup_network_interface *ifm = get_network_interface(ifa->ifa_name);
                ifm->updated = 1;
                network_interfaces_found++;

                if (unlikely(!ifm->configured)) {
                    char var_name[4096 + 1];

                    // this is the first time we see this network interface

                    // remember we configured it
                    ifm->configured = 1;

                    ifm->enabled = enable_new_interfaces;

                    if (likely(ifm->enabled))
                        ifm->enabled = !simple_pattern_matches(excluded_interfaces, ifa->ifa_name);

                    snprintfz(var_name, 4096, "%s:%s", CONFIG_SECTION_GETIFADDRS, ifa->ifa_name);
                    ifm->enabled = config_get_boolean_ondemand(var_name, "enabled", ifm->enabled);

                    if (unlikely(ifm->enabled == CONFIG_BOOLEAN_NO))
                        continue;

                    ifm->do_bandwidth = config_get_boolean_ondemand(var_name, "bandwidth", do_bandwidth);
                    ifm->do_packets   = config_get_boolean_ondemand(var_name, "packets",   do_packets);
                    ifm->do_errors    = config_get_boolean_ondemand(var_name, "errors",    do_errors);
                    ifm->do_drops     = config_get_boolean_ondemand(var_name, "drops",     do_drops);
                    ifm->do_events    = config_get_boolean_ondemand(var_name, "events",    do_events);
                }

                if (unlikely(!ifm->enabled))
                    continue;

                // --------------------------------------------------------------------

                if (ifm->do_bandwidth == CONFIG_BOOLEAN_YES || (ifm->do_bandwidth == CONFIG_BOOLEAN_AUTO &&
                                                                (IFA_DATA(ibytes) || IFA_DATA(obytes)))) {
                    if (unlikely(!ifm->st_bandwidth)) {
                        ifm->st_bandwidth = rrdset_create_localhost("net",
                                                                    ifa->ifa_name,
                                                                    NULL,
                                                                    ifa->ifa_name,
                                                                    "net.net",
                                                                    "Bandwidth",
                                                                    "kilobits/s",
                                                                    "freebsd.plugin",
                                                                    "getifaddrs",
                                                                    NETDATA_CHART_PRIO_FIRST_NET_IFACE,
                                                                    update_every,
                                                                    RRDSET_TYPE_AREA
                        );

                        ifm->rd_bandwidth_in  = rrddim_add(ifm->st_bandwidth, "received", NULL,  8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
                        ifm->rd_bandwidth_out = rrddim_add(ifm->st_bandwidth, "sent",     NULL, -8, BITS_IN_A_KILOBIT, RRD_ALGORITHM_INCREMENTAL);
                    } else
                        rrdset_next(ifm->st_bandwidth);

                    rrddim_set_by_pointer(ifm->st_bandwidth, ifm->rd_bandwidth_in,  IFA_DATA(ibytes));
                    rrddim_set_by_pointer(ifm->st_bandwidth, ifm->rd_bandwidth_out, IFA_DATA(obytes));
                    rrdset_done(ifm->st_bandwidth);
                }

                // --------------------------------------------------------------------

                if (ifm->do_packets == CONFIG_BOOLEAN_YES || (ifm->do_packets == CONFIG_BOOLEAN_AUTO &&
                                                              (IFA_DATA(ipackets) || IFA_DATA(opackets) || IFA_DATA(imcasts) || IFA_DATA(omcasts)))) {
                    if (unlikely(!ifm->st_packets)) {
                        ifm->st_packets = rrdset_create_localhost("net_packets",
                                                                  ifa->ifa_name,
                                                                  NULL,
                                                                  ifa->ifa_name,
                                                                  "net.packets",
                                                                  "Packets",
                                                                  "packets/s",
                                                                  "freebsd.plugin",
                                                                  "getifaddrs",
                                                                  NETDATA_CHART_PRIO_FIRST_NET_PACKETS,
                                                                  update_every,
                                                                  RRDSET_TYPE_LINE
                        );

                        rrdset_flag_set(ifm->st_packets, RRDSET_FLAG_DETAIL);

                        ifm->rd_packets_in    = rrddim_add(ifm->st_packets, "received",           NULL,  1, 1,
                                                           RRD_ALGORITHM_INCREMENTAL);
                        ifm->rd_packets_out   = rrddim_add(ifm->st_packets, "sent",               NULL, -1, 1,
                                                           RRD_ALGORITHM_INCREMENTAL);
                        ifm->rd_packets_m_in  = rrddim_add(ifm->st_packets, "multicast_received", NULL,  1, 1,
                                                           RRD_ALGORITHM_INCREMENTAL);
                        ifm->rd_packets_m_out = rrddim_add(ifm->st_packets, "multicast_sent",     NULL, -1, 1,
                                                           RRD_ALGORITHM_INCREMENTAL);
                    } else
                        rrdset_next(ifm->st_packets);

                    rrddim_set_by_pointer(ifm->st_packets, ifm->rd_packets_in,    IFA_DATA(ipackets));
                    rrddim_set_by_pointer(ifm->st_packets, ifm->rd_packets_out,   IFA_DATA(opackets));
                    rrddim_set_by_pointer(ifm->st_packets, ifm->rd_packets_m_in,  IFA_DATA(imcasts));
                    rrddim_set_by_pointer(ifm->st_packets, ifm->rd_packets_m_out, IFA_DATA(omcasts));
                    rrdset_done(ifm->st_packets);
                }

                // --------------------------------------------------------------------

                if (ifm->do_errors == CONFIG_BOOLEAN_YES || (ifm->do_errors == CONFIG_BOOLEAN_AUTO &&
                                                             (IFA_DATA(ierrors) || IFA_DATA(oerrors)))) {
                    if (unlikely(!ifm->st_errors)) {
                        ifm->st_errors = rrdset_create_localhost("net_errors",
                                                                 ifa->ifa_name,
                                                                 NULL,
                                                                 ifa->ifa_name,
                                                                 "net.errors",
                                                                 "Interface Errors",
                                                                 "errors/s",
                                                                 "freebsd.plugin",
                                                                 "getifaddrs",
                                                                 NETDATA_CHART_PRIO_FIRST_NET_ERRORS,
                                                                 update_every,
                                                                 RRDSET_TYPE_LINE
                        );

                        rrdset_flag_set(ifm->st_errors, RRDSET_FLAG_DETAIL);

                        ifm->rd_errors_in  = rrddim_add(ifm->st_errors, "inbound",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                        ifm->rd_errors_out = rrddim_add(ifm->st_errors, "outbound", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    } else
                        rrdset_next(ifm->st_errors);

                    rrddim_set_by_pointer(ifm->st_errors, ifm->rd_errors_in,  IFA_DATA(ierrors));
                    rrddim_set_by_pointer(ifm->st_errors, ifm->rd_errors_out, IFA_DATA(oerrors));
                    rrdset_done(ifm->st_errors);
                }
                // --------------------------------------------------------------------

                if (ifm->do_drops == CONFIG_BOOLEAN_YES || (ifm->do_drops == CONFIG_BOOLEAN_AUTO &&
                                                            (IFA_DATA(iqdrops)
                                                             #if __FreeBSD__ >= 11
                                                             || IFA_DATA(oqdrops)
#endif
                ))) {
                    if (unlikely(!ifm->st_drops)) {
                        ifm->st_drops = rrdset_create_localhost("net_drops",
                                                                ifa->ifa_name,
                                                                NULL,
                                                                ifa->ifa_name,
                                                                "net.drops",
                                                                "Interface Drops",
                                                                "drops/s",
                                                                "freebsd.plugin",
                                                                "getifaddrs",
                                                                NETDATA_CHART_PRIO_FIRST_NET_DROPS,
                                                                update_every,
                                                                RRDSET_TYPE_LINE
                        );

                        rrdset_flag_set(ifm->st_drops, RRDSET_FLAG_DETAIL);

                        ifm->rd_drops_in  = rrddim_add(ifm->st_drops, "inbound",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
#if __FreeBSD__ >= 11
                        ifm->rd_drops_out = rrddim_add(ifm->st_drops, "outbound", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
#endif
                    } else
                        rrdset_next(ifm->st_drops);

                    rrddim_set_by_pointer(ifm->st_drops, ifm->rd_drops_in,  IFA_DATA(iqdrops));
#if __FreeBSD__ >= 11
                    rrddim_set_by_pointer(ifm->st_drops, ifm->rd_drops_out, IFA_DATA(oqdrops));
#endif
                    rrdset_done(ifm->st_drops);
                }

                // --------------------------------------------------------------------

                if (ifm->do_events == CONFIG_BOOLEAN_YES || (ifm->do_events == CONFIG_BOOLEAN_AUTO &&
                                                             IFA_DATA(collisions))) {
                    if (unlikely(!ifm->st_events)) {
                        ifm->st_events = rrdset_create_localhost("net_events",
                                                                 ifa->ifa_name,
                                                                 NULL,
                                                                 ifa->ifa_name,
                                                                 "net.events",
                                                                 "Network Interface Events",
                                                                 "events/s",
                                                                 "freebsd.plugin",
                                                                 "getifaddrs",
                                                                 NETDATA_CHART_PRIO_FIRST_NET_EVENTS,
                                                                 update_every,
                                                                 RRDSET_TYPE_LINE
                        );

                        rrdset_flag_set(ifm->st_events, RRDSET_FLAG_DETAIL);

                        ifm->rd_events_coll = rrddim_add(ifm->st_events, "collisions", NULL, -1, 1,
                                                         RRD_ALGORITHM_INCREMENTAL);
                    } else
                        rrdset_next(ifm->st_events);

                    rrddim_set_by_pointer(ifm->st_events, ifm->rd_events_coll, IFA_DATA(collisions));
                    rrdset_done(ifm->st_events);
                }
            }

            freeifaddrs(ifap);
        }
    } else {
        error("DISABLED: getifaddrs module");
        return 1;
    }

    network_interfaces_cleanup();

    return 0;
}