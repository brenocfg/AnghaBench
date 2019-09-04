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
struct ocfs2_reservation_map {int dummy; } ;
struct ocfs2_alloc_reservation {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ocfs2_resv_discard (struct ocfs2_reservation_map*,struct ocfs2_alloc_reservation*) ; 
 int /*<<< orphan*/  resv_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ocfs2_resv_discard(struct ocfs2_reservation_map *resmap,
			struct ocfs2_alloc_reservation *resv)
{
	if (resv) {
		spin_lock(&resv_lock);
		__ocfs2_resv_discard(resmap, resv);
		spin_unlock(&resv_lock);
	}
}