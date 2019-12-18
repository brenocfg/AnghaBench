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
struct xsk_map {int /*<<< orphan*/  lock; } ;
struct xdp_sock {int dummy; } ;

/* Variables and functions */
 struct xdp_sock* READ_ONCE (struct xdp_sock*) ; 
 int /*<<< orphan*/  WRITE_ONCE (struct xdp_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsk_map_sock_delete (struct xdp_sock*,struct xdp_sock**) ; 

void xsk_map_try_sock_delete(struct xsk_map *map, struct xdp_sock *xs,
			     struct xdp_sock **map_entry)
{
	spin_lock_bh(&map->lock);
	if (READ_ONCE(*map_entry) == xs) {
		WRITE_ONCE(*map_entry, NULL);
		xsk_map_sock_delete(xs, map_entry);
	}
	spin_unlock_bh(&map->lock);
}