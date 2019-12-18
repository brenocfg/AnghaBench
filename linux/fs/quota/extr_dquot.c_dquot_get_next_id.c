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
struct super_block {int dummy; } ;
struct quota_info {TYPE_1__** ops; } ;
struct kqid {size_t type; } ;
struct TYPE_2__ {int (* get_next_id ) (struct super_block*,struct kqid*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int ESRCH ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  sb_has_quota_active (struct super_block*,size_t) ; 
 int stub1 (struct super_block*,struct kqid*) ; 

int dquot_get_next_id(struct super_block *sb, struct kqid *qid)
{
	struct quota_info *dqopt = sb_dqopt(sb);

	if (!sb_has_quota_active(sb, qid->type))
		return -ESRCH;
	if (!dqopt->ops[qid->type]->get_next_id)
		return -ENOSYS;
	return dqopt->ops[qid->type]->get_next_id(sb, qid);
}