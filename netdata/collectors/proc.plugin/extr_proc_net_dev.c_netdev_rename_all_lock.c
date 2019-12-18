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
struct netdev {struct netdev* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdata_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdata_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ netdev_pending_renames ; 
 int /*<<< orphan*/  netdev_rename (struct netdev*) ; 
 int /*<<< orphan*/  netdev_rename_mutex ; 
 struct netdev* netdev_root ; 

__attribute__((used)) static inline void netdev_rename_all_lock(void) {
    netdata_mutex_lock(&netdev_rename_mutex);

    struct netdev *d;
    for(d = netdev_root; d ; d = d->next)
        netdev_rename(d);

    netdev_pending_renames = 0;
    netdata_mutex_unlock(&netdev_rename_mutex);
}