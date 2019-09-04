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
struct clip_vcc {scalar_t__ xoff; struct atmarp_entry* entry; struct clip_vcc* next; } ;
struct atmarp_entry {TYPE_1__* neigh; void* expires; struct clip_vcc* vccs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; void* used; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_UPDATE_F_ADMIN ; 
 int /*<<< orphan*/  NUD_NONE ; 
 void* jiffies ; 
 int neigh_update (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*,...) ; 

__attribute__((used)) static void unlink_clip_vcc(struct clip_vcc *clip_vcc)
{
	struct atmarp_entry *entry = clip_vcc->entry;
	struct clip_vcc **walk;

	if (!entry) {
		pr_crit("!clip_vcc->entry (clip_vcc %p)\n", clip_vcc);
		return;
	}
	netif_tx_lock_bh(entry->neigh->dev);	/* block clip_start_xmit() */
	entry->neigh->used = jiffies;
	for (walk = &entry->vccs; *walk; walk = &(*walk)->next)
		if (*walk == clip_vcc) {
			int error;

			*walk = clip_vcc->next;	/* atomic */
			clip_vcc->entry = NULL;
			if (clip_vcc->xoff)
				netif_wake_queue(entry->neigh->dev);
			if (entry->vccs)
				goto out;
			entry->expires = jiffies - 1;
			/* force resolution or expiration */
			error = neigh_update(entry->neigh, NULL, NUD_NONE,
					     NEIGH_UPDATE_F_ADMIN, 0);
			if (error)
				pr_crit("neigh_update failed with %d\n", error);
			goto out;
		}
	pr_crit("ATMARP: failed (entry %p, vcc 0x%p)\n", entry, clip_vcc);
out:
	netif_tx_unlock_bh(entry->neigh->dev);
}