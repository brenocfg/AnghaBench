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
struct rsc_mgr {int type; unsigned int avail; unsigned int amount; int /*<<< orphan*/  rscs; struct hw* hw; int /*<<< orphan*/  ctrl_blk; } ;
struct hw {int (* src_mgr_get_ctrl_blk ) (int /*<<< orphan*/ *) ;int (* srcimp_mgr_get_ctrl_blk ) (int /*<<< orphan*/ *) ;int (* amixer_mgr_get_ctrl_blk ) (int /*<<< orphan*/ *) ;int (* daio_mgr_get_ctrl_blk ) (struct hw*,int /*<<< orphan*/ *) ;TYPE_1__* card; } ;
typedef  enum RSCTYP { ____Placeholder_RSCTYP } RSCTYP ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AMIXER 132 
#define  DAIO 131 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_RSCTYP ; 
#define  SRC 130 
#define  SRCIMP 129 
#define  SUM 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ *) ; 
 int stub3 (int /*<<< orphan*/ *) ; 
 int stub4 (struct hw*,int /*<<< orphan*/ *) ; 

int rsc_mgr_init(struct rsc_mgr *mgr, enum RSCTYP type,
		 unsigned int amount, struct hw *hw)
{
	int err = 0;

	mgr->type = NUM_RSCTYP;

	mgr->rscs = kzalloc(((amount + 8 - 1) / 8), GFP_KERNEL);
	if (!mgr->rscs)
		return -ENOMEM;

	switch (type) {
	case SRC:
		err = hw->src_mgr_get_ctrl_blk(&mgr->ctrl_blk);
		break;
	case SRCIMP:
		err = hw->srcimp_mgr_get_ctrl_blk(&mgr->ctrl_blk);
		break;
	case AMIXER:
		err = hw->amixer_mgr_get_ctrl_blk(&mgr->ctrl_blk);
		break;
	case DAIO:
		err = hw->daio_mgr_get_ctrl_blk(hw, &mgr->ctrl_blk);
		break;
	case SUM:
		break;
	default:
		dev_err(hw->card->dev,
			"Invalid resource type value %d!\n", type);
		err = -EINVAL;
		goto error;
	}

	if (err) {
		dev_err(hw->card->dev,
			"Failed to get manager control block!\n");
		goto error;
	}

	mgr->type = type;
	mgr->avail = mgr->amount = amount;
	mgr->hw = hw;

	return 0;

error:
	kfree(mgr->rscs);
	return err;
}