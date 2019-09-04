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
struct gntdev_priv {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  event; } ;
struct gntdev_grant_map {int /*<<< orphan*/  count; scalar_t__ pages; int /*<<< orphan*/  next; TYPE_1__ notify; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int UNMAP_NOTIFY_SEND_EVENT ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtchn_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gntdev_free_map (struct gntdev_grant_map*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pages_mapped ; 
 scalar_t__ populate_freeable_maps ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_grant_pages (struct gntdev_grant_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_ptemod ; 

void gntdev_put_map(struct gntdev_priv *priv, struct gntdev_grant_map *map)
{
	if (!map)
		return;

	if (!refcount_dec_and_test(&map->users))
		return;

	atomic_sub(map->count, &pages_mapped);

	if (map->notify.flags & UNMAP_NOTIFY_SEND_EVENT) {
		notify_remote_via_evtchn(map->notify.event);
		evtchn_put(map->notify.event);
	}

	if (populate_freeable_maps && priv) {
		mutex_lock(&priv->lock);
		list_del(&map->next);
		mutex_unlock(&priv->lock);
	}

	if (map->pages && !use_ptemod)
		unmap_grant_pages(map, 0, map->count);
	gntdev_free_map(map);
}