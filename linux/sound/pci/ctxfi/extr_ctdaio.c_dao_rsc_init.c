#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hw {int (* dao_get_ctrl_blk ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* daio_mgr_commit_write ) (struct hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* daio_mgr_enb_dao ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* daio_mgr_dao_init ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  (* daio_mgr_dsb_dao ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct dao {TYPE_2__ daio; int /*<<< orphan*/ * imappers; int /*<<< orphan*/  ctrl_blk; struct hw* hw; struct daio_mgr* mgr; int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct daio_mgr {TYPE_1__ mgr; } ;
struct daio_desc {int msr; int passthru; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 int /*<<< orphan*/  daio_device_index (int /*<<< orphan*/ ,struct hw*) ; 
 int daio_rsc_init (TYPE_2__*,struct daio_desc const*,struct hw*) ; 
 int /*<<< orphan*/  daio_rsc_uninit (TYPE_2__*) ; 
 int /*<<< orphan*/  dao_ops ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dao_rsc_init(struct dao *dao,
			const struct daio_desc *desc,
			struct daio_mgr *mgr)
{
	struct hw *hw = mgr->mgr.hw;
	unsigned int conf;
	int err;

	err = daio_rsc_init(&dao->daio, desc, mgr->mgr.hw);
	if (err)
		return err;

	dao->imappers = kzalloc(array3_size(sizeof(void *), desc->msr, 2),
				GFP_KERNEL);
	if (!dao->imappers) {
		err = -ENOMEM;
		goto error1;
	}
	dao->ops = &dao_ops;
	dao->mgr = mgr;
	dao->hw = hw;
	err = hw->dao_get_ctrl_blk(&dao->ctrl_blk);
	if (err)
		goto error2;

	hw->daio_mgr_dsb_dao(mgr->mgr.ctrl_blk,
			daio_device_index(dao->daio.type, hw));
	hw->daio_mgr_commit_write(hw, mgr->mgr.ctrl_blk);

	conf = (desc->msr & 0x7) | (desc->passthru << 3);
	hw->daio_mgr_dao_init(mgr->mgr.ctrl_blk,
			daio_device_index(dao->daio.type, hw), conf);
	hw->daio_mgr_enb_dao(mgr->mgr.ctrl_blk,
			daio_device_index(dao->daio.type, hw));
	hw->daio_mgr_commit_write(hw, mgr->mgr.ctrl_blk);

	return 0;

error2:
	kfree(dao->imappers);
	dao->imappers = NULL;
error1:
	daio_rsc_uninit(&dao->daio);
	return err;
}