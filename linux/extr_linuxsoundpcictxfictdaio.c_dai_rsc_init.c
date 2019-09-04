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
struct hw {int (* dai_get_ctrl_blk ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dai_commit_write ) (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dai_srt_set_et ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dai_srt_set_ec ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dai_srt_set_drat ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dai_srt_set_rsr ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct TYPE_4__ {struct hw* hw; } ;
struct daio_mgr {TYPE_1__ mgr; } ;
struct daio_desc {unsigned int msr; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct dai {TYPE_2__ daio; int /*<<< orphan*/  ctrl_blk; struct hw* hw; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  dai_ops ; 
 int /*<<< orphan*/  daio_device_index (int /*<<< orphan*/ ,struct hw*) ; 
 int daio_rsc_init (TYPE_2__*,struct daio_desc const*,struct hw*) ; 
 int /*<<< orphan*/  daio_rsc_uninit (TYPE_2__*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dai_rsc_init(struct dai *dai,
			const struct daio_desc *desc,
			struct daio_mgr *mgr)
{
	int err;
	struct hw *hw = mgr->mgr.hw;
	unsigned int rsr, msr;

	err = daio_rsc_init(&dai->daio, desc, mgr->mgr.hw);
	if (err)
		return err;

	dai->ops = &dai_ops;
	dai->hw = mgr->mgr.hw;
	err = hw->dai_get_ctrl_blk(&dai->ctrl_blk);
	if (err)
		goto error1;

	for (rsr = 0, msr = desc->msr; msr > 1; msr >>= 1)
		rsr++;

	hw->dai_srt_set_rsr(dai->ctrl_blk, rsr);
	hw->dai_srt_set_drat(dai->ctrl_blk, 0);
	/* default to disabling control of a SRC */
	hw->dai_srt_set_ec(dai->ctrl_blk, 0);
	hw->dai_srt_set_et(dai->ctrl_blk, 0); /* default to disabling SRT */
	hw->dai_commit_write(hw,
		daio_device_index(dai->daio.type, dai->hw), dai->ctrl_blk);

	return 0;

error1:
	daio_rsc_uninit(&dai->daio);
	return err;
}