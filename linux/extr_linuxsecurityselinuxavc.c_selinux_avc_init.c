#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lru_hint; int /*<<< orphan*/  active_nodes; int /*<<< orphan*/ * slots_lock; int /*<<< orphan*/ * slots; } ;
struct selinux_avc {TYPE_1__ avc_cache; int /*<<< orphan*/  avc_cache_threshold; } ;

/* Variables and functions */
 int AVC_CACHE_SLOTS ; 
 int /*<<< orphan*/  AVC_DEF_CACHE_THRESHOLD ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct selinux_avc selinux_avc ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void selinux_avc_init(struct selinux_avc **avc)
{
	int i;

	selinux_avc.avc_cache_threshold = AVC_DEF_CACHE_THRESHOLD;
	for (i = 0; i < AVC_CACHE_SLOTS; i++) {
		INIT_HLIST_HEAD(&selinux_avc.avc_cache.slots[i]);
		spin_lock_init(&selinux_avc.avc_cache.slots_lock[i]);
	}
	atomic_set(&selinux_avc.avc_cache.active_nodes, 0);
	atomic_set(&selinux_avc.avc_cache.lru_hint, 0);
	*avc = &selinux_avc;
}