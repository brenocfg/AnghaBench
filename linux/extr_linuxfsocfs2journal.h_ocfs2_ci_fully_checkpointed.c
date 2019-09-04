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
struct ocfs2_journal {int /*<<< orphan*/  j_trans_id; } ;
struct ocfs2_caching_info {int /*<<< orphan*/  ci_last_trans; } ;
struct TYPE_2__ {struct ocfs2_journal* journal; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trans_inc_lock ; 

__attribute__((used)) static inline int ocfs2_ci_fully_checkpointed(struct ocfs2_caching_info *ci)
{
	int ret;
	struct ocfs2_journal *journal =
		OCFS2_SB(ocfs2_metadata_cache_get_super(ci))->journal;

	spin_lock(&trans_inc_lock);
	ret = time_after(journal->j_trans_id, ci->ci_last_trans);
	spin_unlock(&trans_inc_lock);
	return ret;
}