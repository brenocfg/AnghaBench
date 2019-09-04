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
struct swap_info_struct {int /*<<< orphan*/  lock; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_cluster (struct swap_cluster_info*) ; 

__attribute__((used)) static inline void unlock_cluster_or_swap_info(struct swap_info_struct *si,
					       struct swap_cluster_info *ci)
{
	if (ci)
		unlock_cluster(ci);
	else
		spin_unlock(&si->lock);
}