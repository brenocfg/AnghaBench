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
struct ocfs2_journal {int /*<<< orphan*/  j_trans_id; } ;
struct ocfs2_caching_info {int /*<<< orphan*/  ci_last_trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trans_inc_lock ; 

__attribute__((used)) static inline void ocfs2_set_ci_lock_trans(struct ocfs2_journal *journal,
					   struct ocfs2_caching_info *ci)
{
	spin_lock(&trans_inc_lock);
	ci->ci_last_trans = journal->j_trans_id;
	spin_unlock(&trans_inc_lock);
}