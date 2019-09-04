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
struct ocfs2_truncate_log {TYPE_1__* tl_recs; int /*<<< orphan*/  tl_used; } ;
struct TYPE_2__ {int /*<<< orphan*/  t_clusters; int /*<<< orphan*/  t_start; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_truncate_log_can_coalesce(struct ocfs2_truncate_log *tl,
					   unsigned int new_start)
{
	unsigned int tail_index;
	unsigned int current_tail;

	/* No records, nothing to coalesce */
	if (!le16_to_cpu(tl->tl_used))
		return 0;

	tail_index = le16_to_cpu(tl->tl_used) - 1;
	current_tail = le32_to_cpu(tl->tl_recs[tail_index].t_start);
	current_tail += le32_to_cpu(tl->tl_recs[tail_index].t_clusters);

	return current_tail == new_start;
}