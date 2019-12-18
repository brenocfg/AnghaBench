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
struct swap_info_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  cluster_info; int /*<<< orphan*/  swap_map; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enable_swap_info (struct swap_info_struct*) ; 
 int /*<<< orphan*/  setup_swap_info (struct swap_info_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_lock ; 

__attribute__((used)) static void reinsert_swap_info(struct swap_info_struct *p)
{
	spin_lock(&swap_lock);
	spin_lock(&p->lock);
	setup_swap_info(p, p->prio, p->swap_map, p->cluster_info);
	_enable_swap_info(p);
	spin_unlock(&p->lock);
	spin_unlock(&swap_lock);
}