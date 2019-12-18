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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int GETSYSCTL_SIMPLE (char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 size_t TCPS_ESTABLISHED ; 
 int TCP_NSTATES ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_net_inet_tcp_states(int update_every, usec_t dt) {
    (void)dt;
    static int mib[4] = {0, 0, 0, 0};
    uint64_t tcps_states[TCP_NSTATES];

    // see http://net-snmp.sourceforge.net/docs/mibs/tcp.html
    if (unlikely(GETSYSCTL_SIMPLE("net.inet.tcp.states", mib, tcps_states))) {
        error("DISABLED: ipv4.tcpsock chart");
        error("DISABLED: net.inet.tcp.states module");
        return 1;
    } else {

        // --------------------------------------------------------------------

        static RRDSET *st = NULL;
        static RRDDIM *rd = NULL;

        if (unlikely(!st)) {
            st = rrdset_create_localhost(
                    "ipv4",
                    "tcpsock",
                    NULL,
                    "tcp",
                    NULL,
                    "IPv4 TCP Connections",
                    "active connections",
                    "freebsd.plugin",
                    "net.inet.tcp.states",
                    2500,
                    update_every,
                    RRDSET_TYPE_LINE
            );

            rd = rrddim_add(st, "CurrEstab", "connections", 1, 1, RRD_ALGORITHM_ABSOLUTE);
        } else
            rrdset_next(st);

        rrddim_set_by_pointer(st, rd, tcps_states[TCPS_ESTABLISHED]);
        rrdset_done(st);
    }

    return 0;
}