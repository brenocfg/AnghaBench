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
typedef  scalar_t__ u64 ;
struct ocfs2_blockcheck_stats {int /*<<< orphan*/  b_lock; scalar_t__ b_failure_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_blockcheck_inc_failure(struct ocfs2_blockcheck_stats *stats)
{
	u64 new_count;

	if (!stats)
		return;

	spin_lock(&stats->b_lock);
	stats->b_failure_count++;
	new_count = stats->b_failure_count;
	spin_unlock(&stats->b_lock);

	if (!new_count)
		mlog(ML_NOTICE, "Checksum failure count has wrapped\n");
}