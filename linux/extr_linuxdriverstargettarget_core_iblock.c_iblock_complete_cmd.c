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
typedef  int /*<<< orphan*/  u8 ;
struct se_cmd {struct iblock_req* priv; } ;
struct iblock_req {int /*<<< orphan*/  ib_bio_err_cnt; int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iblock_req*) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iblock_complete_cmd(struct se_cmd *cmd)
{
	struct iblock_req *ibr = cmd->priv;
	u8 status;

	if (!refcount_dec_and_test(&ibr->pending))
		return;

	if (atomic_read(&ibr->ib_bio_err_cnt))
		status = SAM_STAT_CHECK_CONDITION;
	else
		status = SAM_STAT_GOOD;

	target_complete_cmd(cmd, status);
	kfree(ibr);
}