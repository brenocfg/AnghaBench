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
struct rds_sock {int /*<<< orphan*/  rs_bound_port; int /*<<< orphan*/  rs_bound_addr; int /*<<< orphan*/  rs_cong_list; } ;
struct rds_cong_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_cong_clear_bit (struct rds_cong_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_cong_lock ; 
 int /*<<< orphan*/  rds_cong_monitor_lock ; 
 int /*<<< orphan*/  rds_cong_queue_updates (struct rds_cong_map*) ; 
 scalar_t__ rds_cong_test_bit (struct rds_cong_map*,int /*<<< orphan*/ ) ; 
 struct rds_cong_map* rds_cong_tree_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rds_cong_remove_socket(struct rds_sock *rs)
{
	unsigned long flags;
	struct rds_cong_map *map;

	write_lock_irqsave(&rds_cong_monitor_lock, flags);
	list_del_init(&rs->rs_cong_list);
	write_unlock_irqrestore(&rds_cong_monitor_lock, flags);

	/* update congestion map for now-closed port */
	spin_lock_irqsave(&rds_cong_lock, flags);
	map = rds_cong_tree_walk(&rs->rs_bound_addr, NULL);
	spin_unlock_irqrestore(&rds_cong_lock, flags);

	if (map && rds_cong_test_bit(map, rs->rs_bound_port)) {
		rds_cong_clear_bit(map, rs->rs_bound_port);
		rds_cong_queue_updates(map);
	}
}