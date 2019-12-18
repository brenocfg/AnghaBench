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
struct netdev_rename {int processed; } ;
struct netdev {int /*<<< orphan*/  hash; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_pending_renames ; 
 int /*<<< orphan*/  netdev_rename_cgroup (struct netdev*,struct netdev_rename*) ; 
 struct netdev_rename* netdev_rename_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void netdev_rename(struct netdev *d) {
    struct netdev_rename *r = netdev_rename_find(d->name, d->hash);
    if(unlikely(r && !r->processed)) {
        netdev_rename_cgroup(d, r);
        r->processed = 1;
        netdev_pending_renames--;
    }
}