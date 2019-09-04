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
struct netdev_rename {scalar_t__ hash; int /*<<< orphan*/  host_device; struct netdev_rename* next; } ;

/* Variables and functions */
 struct netdev_rename* netdev_rename_root ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netdev_rename *netdev_rename_find(const char *host_device, uint32_t hash) {
    struct netdev_rename *r;

    for(r = netdev_rename_root; r ; r = r->next)
        if(r->hash == hash && !strcmp(host_device, r->host_device))
            return r;

    return NULL;
}