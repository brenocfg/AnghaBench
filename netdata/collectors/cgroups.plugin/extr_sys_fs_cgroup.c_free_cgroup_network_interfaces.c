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
struct cgroup_network_interface {scalar_t__ container_device; scalar_t__ host_device; struct cgroup_network_interface* next; } ;
struct cgroup {struct cgroup_network_interface* interfaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (void*) ; 
 int /*<<< orphan*/  netdev_rename_device_del (scalar_t__) ; 

__attribute__((used)) static inline void free_cgroup_network_interfaces(struct cgroup *cg) {
    while(cg->interfaces) {
        struct cgroup_network_interface *i = cg->interfaces;
        cg->interfaces = i->next;

        // delete the registration of proc_net_dev rename
        netdev_rename_device_del(i->host_device);

        freez((void *)i->host_device);
        freez((void *)i->container_device);
        freez((void *)i);
    }
}