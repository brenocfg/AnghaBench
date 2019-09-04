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
 struct swap_cluster_info* lock_cluster (struct swap_info_struct*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct swap_cluster_info *lock_cluster_or_swap_info(
		struct swap_info_struct *si, unsigned long offset)
{
	struct swap_cluster_info *ci;

	/* Try to use fine-grained SSD-style locking if available: */
	ci = lock_cluster(si, offset);
	/* Otherwise, fall back to traditional, coarse locking: */
	if (!ci)
		spin_lock(&si->lock);

	return ci;
}