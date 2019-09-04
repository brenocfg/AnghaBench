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
struct cgroup_network_interface {scalar_t__ hash; char const* name; struct cgroup_network_interface* next; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 struct cgroup_network_interface* callocz (int,int) ; 
 int /*<<< orphan*/  network_interfaces_added ; 
 struct cgroup_network_interface* network_interfaces_last_used ; 
 struct cgroup_network_interface* network_interfaces_root ; 
 scalar_t__ simple_hash (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 char const* strdupz (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct cgroup_network_interface *get_network_interface(const char *name) {
    struct cgroup_network_interface *ifm;

    uint32_t hash = simple_hash(name);

    // search it, from the last position to the end
    for(ifm = network_interfaces_last_used ; ifm ; ifm = ifm->next) {
        if (unlikely(hash == ifm->hash && !strcmp(name, ifm->name))) {
            network_interfaces_last_used = ifm->next;
            return ifm;
        }
    }

    // search it from the beginning to the last position we used
    for(ifm = network_interfaces_root ; ifm != network_interfaces_last_used ; ifm = ifm->next) {
        if (unlikely(hash == ifm->hash && !strcmp(name, ifm->name))) {
            network_interfaces_last_used = ifm->next;
            return ifm;
        }
    }

    // create a new one
    ifm = callocz(1, sizeof(struct cgroup_network_interface));
    ifm->name = strdupz(name);
    ifm->hash = simple_hash(ifm->name);
    ifm->len = strlen(ifm->name);
    network_interfaces_added++;

    // link it to the end
    if (network_interfaces_root) {
        struct cgroup_network_interface *e;
        for(e = network_interfaces_root; e->next ; e = e->next) ;
        e->next = ifm;
    }
    else
        network_interfaces_root = ifm;

    return ifm;
}