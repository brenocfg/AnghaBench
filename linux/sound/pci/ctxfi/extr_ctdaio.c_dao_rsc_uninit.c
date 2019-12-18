#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t msr; } ;
struct TYPE_6__ {TYPE_2__ rscl; } ;
struct dao {TYPE_3__ daio; int /*<<< orphan*/ * ctrl_blk; TYPE_1__* hw; scalar_t__* imappers; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dao_put_ctrl_blk ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  daio_rsc_uninit (TYPE_3__*) ; 
 int /*<<< orphan*/  dao_clear_left_input (struct dao*) ; 
 int /*<<< orphan*/  dao_clear_right_input (struct dao*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dao_rsc_uninit(struct dao *dao)
{
	if (dao->imappers) {
		if (dao->imappers[0])
			dao_clear_left_input(dao);

		if (dao->imappers[dao->daio.rscl.msr])
			dao_clear_right_input(dao);

		kfree(dao->imappers);
		dao->imappers = NULL;
	}
	dao->hw->dao_put_ctrl_blk(dao->ctrl_blk);
	dao->hw = dao->ctrl_blk = NULL;
	daio_rsc_uninit(&dao->daio);

	return 0;
}