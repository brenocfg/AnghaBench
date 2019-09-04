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
struct se_cmd {struct iblock_req* priv; } ;
struct iblock_req {int /*<<< orphan*/  ib_bio_err_cnt; } ;
struct bio {scalar_t__ bi_status; struct se_cmd* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  iblock_complete_cmd (struct se_cmd*) ; 
 int /*<<< orphan*/  pr_err (char*,struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static void iblock_bio_done(struct bio *bio)
{
	struct se_cmd *cmd = bio->bi_private;
	struct iblock_req *ibr = cmd->priv;

	if (bio->bi_status) {
		pr_err("bio error: %p,  err: %d\n", bio, bio->bi_status);
		/*
		 * Bump the ib_bio_err_cnt and release bio.
		 */
		atomic_inc(&ibr->ib_bio_err_cnt);
		smp_mb__after_atomic();
	}

	bio_put(bio);

	iblock_complete_cmd(cmd);
}