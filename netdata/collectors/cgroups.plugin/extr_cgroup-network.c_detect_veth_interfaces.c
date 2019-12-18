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
struct iface {scalar_t__ ifindex; scalar_t__ iflink; int /*<<< orphan*/  device; struct iface* next; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eligible_ifaces (struct iface*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  free_host_ifaces (struct iface*) ; 
 scalar_t__ iface_is_eligible (struct iface*) ; 
 int /*<<< orphan*/  info (char*,scalar_t__) ; 
 int /*<<< orphan*/ * netdata_configured_host_prefix ; 
 struct iface* read_proc_net_dev (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ switch_namespace (int /*<<< orphan*/ *,scalar_t__) ; 

void detect_veth_interfaces(pid_t pid) {
    struct iface *cgroup = NULL;
    struct iface *host, *h, *c;

    host = read_proc_net_dev("host", netdata_configured_host_prefix);
    if(!host) {
        errno = 0;
        error("cannot read host interface list.");
        goto cleanup;
    }

    if(!eligible_ifaces(host)) {
        errno = 0;
        error("there are no double-linked host interfaces available.");
        goto cleanup;
    }

    if(switch_namespace(netdata_configured_host_prefix, pid)) {
        errno = 0;
        error("cannot switch to the namespace of pid %u", (unsigned int) pid);
        goto cleanup;
    }

#ifdef NETDATA_INTERNAL_CHECKS
    info("switched to namespaces of pid %d", pid);
#endif

    cgroup = read_proc_net_dev("cgroup", NULL);
    if(!cgroup) {
        errno = 0;
        error("cannot read cgroup interface list.");
        goto cleanup;
    }

    if(!eligible_ifaces(cgroup)) {
        errno = 0;
        error("there are not double-linked cgroup interfaces available.");
        goto cleanup;
    }

    for(h = host; h ; h = h->next) {
        if(iface_is_eligible(h)) {
            for (c = cgroup; c; c = c->next) {
                if(iface_is_eligible(c) && h->ifindex == c->iflink && h->iflink == c->ifindex) {
                    add_device(h->device, c->device);
                }
            }
        }
    }

cleanup:
    free_host_ifaces(cgroup);
    free_host_ifaces(host);
}