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
typedef  void* u32 ;
struct rsc {int type; int /*<<< orphan*/ * ctrl_blk; int /*<<< orphan*/ * ops; struct hw* hw; void* msr; void* conj; void* idx; } ;
struct hw {int (* src_rsc_get_ctrl_blk ) (int /*<<< orphan*/ **) ;int (* amixer_rsc_get_ctrl_blk ) (int /*<<< orphan*/ **) ;TYPE_1__* card; } ;
typedef  enum RSCTYP { ____Placeholder_RSCTYP } RSCTYP ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AMIXER 132 
#define  DAIO 131 
 int EINVAL ; 
#define  SRC 130 
#define  SRCIMP 129 
#define  SUM 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rsc_generic_ops ; 
 int stub1 (int /*<<< orphan*/ **) ; 
 int stub2 (int /*<<< orphan*/ **) ; 

int
rsc_init(struct rsc *rsc, u32 idx, enum RSCTYP type, u32 msr, struct hw *hw)
{
	int err = 0;

	rsc->idx = idx;
	rsc->conj = idx;
	rsc->type = type;
	rsc->msr = msr;
	rsc->hw = hw;
	rsc->ops = &rsc_generic_ops;
	if (!hw) {
		rsc->ctrl_blk = NULL;
		return 0;
	}

	switch (type) {
	case SRC:
		err = hw->src_rsc_get_ctrl_blk(&rsc->ctrl_blk);
		break;
	case AMIXER:
		err = hw->amixer_rsc_get_ctrl_blk(&rsc->ctrl_blk);
		break;
	case SRCIMP:
	case SUM:
	case DAIO:
		break;
	default:
		dev_err(((struct hw *)hw)->card->dev,
			"Invalid resource type value %d!\n", type);
		return -EINVAL;
	}

	if (err) {
		dev_err(((struct hw *)hw)->card->dev,
			"Failed to get resource control block!\n");
		return err;
	}

	return 0;
}