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
struct quota_info {int /*<<< orphan*/  dqio_sem; } ;
struct kqid {int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqi_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int qtree_get_next_id (int /*<<< orphan*/ ,struct kqid*) ; 
 TYPE_1__* sb_dqinfo (struct super_block*,int /*<<< orphan*/ ) ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int v2_get_next_id(struct super_block *sb, struct kqid *qid)
{
	struct quota_info *dqopt = sb_dqopt(sb);
	int ret;

	down_read(&dqopt->dqio_sem);
	ret = qtree_get_next_id(sb_dqinfo(sb, qid->type)->dqi_priv, qid);
	up_read(&dqopt->dqio_sem);
	return ret;
}