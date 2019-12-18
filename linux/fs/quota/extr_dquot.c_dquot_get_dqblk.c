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
struct super_block {int dummy; } ;
struct qc_dqblk {int dummy; } ;
struct kqid {int dummy; } ;
struct dquot {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dquot*) ; 
 int PTR_ERR (struct dquot*) ; 
 int /*<<< orphan*/  do_get_dqblk (struct dquot*,struct qc_dqblk*) ; 
 struct dquot* dqget (struct super_block*,struct kqid) ; 
 int /*<<< orphan*/  dqput (struct dquot*) ; 

int dquot_get_dqblk(struct super_block *sb, struct kqid qid,
		    struct qc_dqblk *di)
{
	struct dquot *dquot;

	dquot = dqget(sb, qid);
	if (IS_ERR(dquot))
		return PTR_ERR(dquot);
	do_get_dqblk(dquot, di);
	dqput(dquot);

	return 0;
}