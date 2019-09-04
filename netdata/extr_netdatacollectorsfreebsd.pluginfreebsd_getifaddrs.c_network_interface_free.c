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
struct cgroup_network_interface {struct cgroup_network_interface* name; int /*<<< orphan*/  st_events; int /*<<< orphan*/  st_drops; int /*<<< orphan*/  st_errors; int /*<<< orphan*/  st_packets; int /*<<< orphan*/  st_bandwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (struct cgroup_network_interface*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_interfaces_added ; 
 int /*<<< orphan*/  rrdset_is_obsolete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void network_interface_free(struct cgroup_network_interface *ifm) {
    if (likely(ifm->st_bandwidth))
        rrdset_is_obsolete(ifm->st_bandwidth);
    if (likely(ifm->st_packets))
        rrdset_is_obsolete(ifm->st_packets);
    if (likely(ifm->st_errors))
        rrdset_is_obsolete(ifm->st_errors);
    if (likely(ifm->st_drops))
        rrdset_is_obsolete(ifm->st_drops);
    if (likely(ifm->st_events))
        rrdset_is_obsolete(ifm->st_events);

    network_interfaces_added--;
    freez(ifm->name);
    freez(ifm);
}