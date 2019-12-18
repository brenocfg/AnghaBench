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
struct netdev {scalar_t__ hash; char const* name; struct netdev* next; int /*<<< orphan*/  priority; void* chart_family; void* chart_id_net_packets; void* chart_id_net_fifo; void* chart_id_net_events; void* chart_id_net_errors; void* chart_id_net_drops; void* chart_id_net_compressed; void* chart_id_net_bytes; void* chart_type_net_packets; void* chart_type_net_fifo; void* chart_type_net_events; void* chart_type_net_errors; void* chart_type_net_drops; void* chart_type_net_compressed; void* chart_type_net_bytes; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDATA_CHART_PRIO_FIRST_NET_IFACE ; 
 struct netdev* callocz (int,int) ; 
 int /*<<< orphan*/  netdev_added ; 
 struct netdev* netdev_last_used ; 
 int /*<<< orphan*/  netdev_rename_lock (struct netdev*) ; 
 struct netdev* netdev_root ; 
 scalar_t__ simple_hash (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 void* strdupz (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct netdev *get_netdev(const char *name) {
    struct netdev *d;

    uint32_t hash = simple_hash(name);

    // search it, from the last position to the end
    for(d = netdev_last_used ; d ; d = d->next) {
        if(unlikely(hash == d->hash && !strcmp(name, d->name))) {
            netdev_last_used = d->next;
            return d;
        }
    }

    // search it from the beginning to the last position we used
    for(d = netdev_root ; d != netdev_last_used ; d = d->next) {
        if(unlikely(hash == d->hash && !strcmp(name, d->name))) {
            netdev_last_used = d->next;
            return d;
        }
    }

    // create a new one
    d = callocz(1, sizeof(struct netdev));
    d->name = strdupz(name);
    d->hash = simple_hash(d->name);
    d->len = strlen(d->name);

    d->chart_type_net_bytes      = strdupz("net");
    d->chart_type_net_compressed = strdupz("net_compressed");
    d->chart_type_net_drops      = strdupz("net_drops");
    d->chart_type_net_errors     = strdupz("net_errors");
    d->chart_type_net_events     = strdupz("net_events");
    d->chart_type_net_fifo       = strdupz("net_fifo");
    d->chart_type_net_packets    = strdupz("net_packets");

    d->chart_id_net_bytes      = strdupz(d->name);
    d->chart_id_net_compressed = strdupz(d->name);
    d->chart_id_net_drops      = strdupz(d->name);
    d->chart_id_net_errors     = strdupz(d->name);
    d->chart_id_net_events     = strdupz(d->name);
    d->chart_id_net_fifo       = strdupz(d->name);
    d->chart_id_net_packets    = strdupz(d->name);

    d->chart_family = strdupz(d->name);
    d->priority = NETDATA_CHART_PRIO_FIRST_NET_IFACE;

    netdev_rename_lock(d);

    netdev_added++;

    // link it to the end
    if(netdev_root) {
        struct netdev *e;
        for(e = netdev_root; e->next ; e = e->next) ;
        e->next = d;
    }
    else
        netdev_root = d;

    return d;
}