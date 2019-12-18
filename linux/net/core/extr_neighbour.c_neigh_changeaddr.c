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
struct net_device {int dummy; } ;
struct neigh_table {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  neigh_flush_dev (struct neigh_table*,struct net_device*,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void neigh_changeaddr(struct neigh_table *tbl, struct net_device *dev)
{
	write_lock_bh(&tbl->lock);
	neigh_flush_dev(tbl, dev, false);
	write_unlock_bh(&tbl->lock);
}