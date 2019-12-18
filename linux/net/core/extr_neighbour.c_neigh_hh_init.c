#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_2__* header_ops; } ;
struct hh_cache {int /*<<< orphan*/  hh_len; } ;
struct neighbour {int /*<<< orphan*/  lock; struct hh_cache hh; TYPE_1__* tbl; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  (* cache ) (struct neighbour*,struct hh_cache*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct neighbour*,struct hh_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neigh_hh_init(struct neighbour *n)
{
	struct net_device *dev = n->dev;
	__be16 prot = n->tbl->protocol;
	struct hh_cache	*hh = &n->hh;

	write_lock_bh(&n->lock);

	/* Only one thread can come in here and initialize the
	 * hh_cache entry.
	 */
	if (!hh->hh_len)
		dev->header_ops->cache(n, hh, prot);

	write_unlock_bh(&n->lock);
}