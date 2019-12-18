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
struct ocfs2_super {TYPE_1__* journal; } ;
struct ocfs2_caching_info {int /*<<< orphan*/  ci_created_trans; } ;
struct TYPE_2__ {int /*<<< orphan*/  j_trans_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trans_inc_lock ; 

__attribute__((used)) static inline void ocfs2_ci_set_new(struct ocfs2_super *osb,
				    struct ocfs2_caching_info *ci)
{
	spin_lock(&trans_inc_lock);
	ci->ci_created_trans = osb->journal->j_trans_id;
	spin_unlock(&trans_inc_lock);
}