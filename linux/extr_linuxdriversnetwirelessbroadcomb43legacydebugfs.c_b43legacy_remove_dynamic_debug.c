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
struct b43legacy_wldev {struct b43legacy_dfsentry* dfsentry; } ;
struct b43legacy_dfsentry {int /*<<< orphan*/ * dyn_debug_dentries; } ;

/* Variables and functions */
 int __B43legacy_NR_DYNDBG ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43legacy_remove_dynamic_debug(struct b43legacy_wldev *dev)
{
	struct b43legacy_dfsentry *e = dev->dfsentry;
	int i;

	for (i = 0; i < __B43legacy_NR_DYNDBG; i++)
		debugfs_remove(e->dyn_debug_dentries[i]);
}