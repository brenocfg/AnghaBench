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
struct netdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdata_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdata_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_rename (struct netdev*) ; 
 int /*<<< orphan*/  netdev_rename_mutex ; 

__attribute__((used)) static inline void netdev_rename_lock(struct netdev *d) {
    netdata_mutex_lock(&netdev_rename_mutex);
    netdev_rename(d);
    netdata_mutex_unlock(&netdev_rename_mutex);
}