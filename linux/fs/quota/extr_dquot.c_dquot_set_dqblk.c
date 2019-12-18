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
 int do_set_dqblk (struct dquot*,struct qc_dqblk*) ; 
 struct dquot* dqget (struct super_block*,struct kqid) ; 
 int /*<<< orphan*/  dqput (struct dquot*) ; 

int dquot_set_dqblk(struct super_block *sb, struct kqid qid,
		  struct qc_dqblk *di)
{
	struct dquot *dquot;
	int rc;

	dquot = dqget(sb, qid);
	if (IS_ERR(dquot)) {
		rc = PTR_ERR(dquot);
		goto out;
	}
	rc = do_set_dqblk(dquot, di);
	dqput(dquot);
out:
	return rc;
}