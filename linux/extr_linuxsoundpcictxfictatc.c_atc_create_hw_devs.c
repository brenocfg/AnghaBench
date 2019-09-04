#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hw {int (* card_init ) (struct hw*,struct card_conf*) ;TYPE_1__* card; } ;
struct ct_atc {TYPE_1__* card; int /*<<< orphan*/ * rsc_mgrs; struct hw* hw; int /*<<< orphan*/  msr; int /*<<< orphan*/  rsr; int /*<<< orphan*/  model; int /*<<< orphan*/  chip_type; int /*<<< orphan*/  pci; } ;
struct card_conf {int /*<<< orphan*/  vm_pgt_phys; int /*<<< orphan*/  msr; int /*<<< orphan*/  rsr; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int (* create ) (struct hw*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NUM_RSCTYP ; 
 int /*<<< orphan*/  atc_get_ptp_phys (struct ct_atc*,int /*<<< orphan*/ ) ; 
 int create_hw_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hw**) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* rsc_mgr_funcs ; 
 int stub1 (struct hw*,struct card_conf*) ; 
 int stub2 (struct hw*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atc_create_hw_devs(struct ct_atc *atc)
{
	struct hw *hw;
	struct card_conf info = {0};
	int i, err;

	err = create_hw_obj(atc->pci, atc->chip_type, atc->model, &hw);
	if (err) {
		dev_err(atc->card->dev, "Failed to create hw obj!!!\n");
		return err;
	}
	hw->card = atc->card;
	atc->hw = hw;

	/* Initialize card hardware. */
	info.rsr = atc->rsr;
	info.msr = atc->msr;
	info.vm_pgt_phys = atc_get_ptp_phys(atc, 0);
	err = hw->card_init(hw, &info);
	if (err < 0)
		return err;

	for (i = 0; i < NUM_RSCTYP; i++) {
		if (!rsc_mgr_funcs[i].create)
			continue;

		err = rsc_mgr_funcs[i].create(atc->hw, &atc->rsc_mgrs[i]);
		if (err) {
			dev_err(atc->card->dev,
				"Failed to create rsc_mgr %d!!!\n", i);
			return err;
		}
	}

	return 0;
}