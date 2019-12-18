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
struct cgroup_network_interface {struct cgroup_network_interface* next; scalar_t__ updated; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  network_interface_free (struct cgroup_network_interface*) ; 
 scalar_t__ network_interfaces_added ; 
 scalar_t__ network_interfaces_found ; 
 struct cgroup_network_interface* network_interfaces_last_used ; 
 struct cgroup_network_interface* network_interfaces_root ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void network_interfaces_cleanup() {
    if (likely(network_interfaces_found == network_interfaces_added)) return;

    struct cgroup_network_interface *ifm = network_interfaces_root, *last = NULL;
    while(ifm) {
        if (unlikely(!ifm->updated)) {
            // info("Removing network interface '%s', linked after '%s'", ifm->name, last?last->name:"ROOT");

            if (network_interfaces_last_used == ifm)
                network_interfaces_last_used = last;

            struct cgroup_network_interface *t = ifm;

            if (ifm == network_interfaces_root || !last)
                network_interfaces_root = ifm = ifm->next;

            else
                last->next = ifm = ifm->next;

            t->next = NULL;
            network_interface_free(t);
        }
        else {
            last = ifm;
            ifm->updated = 0;
            ifm = ifm->next;
        }
    }
}