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
typedef  scalar_t__ uint32_t ;
struct netdev_rename {scalar_t__ hash; scalar_t__ container_device; scalar_t__ container_name; scalar_t__ host_device; int /*<<< orphan*/  processed; struct netdev_rename* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (void*) ; 
 int /*<<< orphan*/  info (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  netdata_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdata_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_pending_renames ; 
 int /*<<< orphan*/  netdev_rename_mutex ; 
 struct netdev_rename* netdev_rename_root ; 
 scalar_t__ simple_hash (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

void netdev_rename_device_del(const char *host_device) {
    netdata_mutex_lock(&netdev_rename_mutex);

    struct netdev_rename *r, *last = NULL;

    uint32_t hash = simple_hash(host_device);
    for(r = netdev_rename_root; r ; last = r, r = r->next) {
        if (r->hash == hash && !strcmp(host_device, r->host_device)) {
            if (netdev_rename_root == r)
                netdev_rename_root = r->next;
            else if (last)
                last->next = r->next;

            if(!r->processed)
                netdev_pending_renames--;

            info("CGROUP: unregistered network interface rename for '%s' as '%s' under '%s'", r->host_device, r->container_device, r->container_name);

            freez((void *) r->host_device);
            freez((void *) r->container_name);
            freez((void *) r->container_device);
            freez((void *) r);
            break;
        }
    }

    netdata_mutex_unlock(&netdev_rename_mutex);
}