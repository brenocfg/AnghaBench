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
struct swap_info_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  type; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enable_swap_info (struct swap_info_struct*) ; 
 int /*<<< orphan*/  frontswap_init (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  setup_swap_info (struct swap_info_struct*,int,unsigned char*,struct swap_cluster_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_lock ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void enable_swap_info(struct swap_info_struct *p, int prio,
				unsigned char *swap_map,
				struct swap_cluster_info *cluster_info,
				unsigned long *frontswap_map)
{
	frontswap_init(p->type, frontswap_map);
	spin_lock(&swap_lock);
	spin_lock(&p->lock);
	setup_swap_info(p, prio, swap_map, cluster_info);
	spin_unlock(&p->lock);
	spin_unlock(&swap_lock);
	/*
	 * Guarantee swap_map, cluster_info, etc. fields are valid
	 * between get/put_swap_device() if SWP_VALID bit is set
	 */
	synchronize_rcu();
	spin_lock(&swap_lock);
	spin_lock(&p->lock);
	_enable_swap_info(p);
	spin_unlock(&p->lock);
	spin_unlock(&swap_lock);
}