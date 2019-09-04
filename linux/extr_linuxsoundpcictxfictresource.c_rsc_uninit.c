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
struct rsc {int type; scalar_t__ msr; scalar_t__ conj; scalar_t__ idx; int /*<<< orphan*/ * ctrl_blk; TYPE_2__* hw; } ;
struct hw {TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* amixer_rsc_put_ctrl_blk ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* src_rsc_put_ctrl_blk ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AMIXER 131 
#define  DAIO 130 
 int NUM_RSCTYP ; 
#define  SRC 129 
#define  SUM 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

int rsc_uninit(struct rsc *rsc)
{
	if ((NULL != rsc->hw) && (NULL != rsc->ctrl_blk)) {
		switch (rsc->type) {
		case SRC:
			rsc->hw->src_rsc_put_ctrl_blk(rsc->ctrl_blk);
			break;
		case AMIXER:
			rsc->hw->amixer_rsc_put_ctrl_blk(rsc->ctrl_blk);
			break;
		case SUM:
		case DAIO:
			break;
		default:
			dev_err(((struct hw *)rsc->hw)->card->dev,
				"Invalid resource type value %d!\n",
				rsc->type);
			break;
		}

		rsc->hw = rsc->ctrl_blk = NULL;
	}

	rsc->idx = rsc->conj = 0;
	rsc->type = NUM_RSCTYP;
	rsc->msr = 0;

	return 0;
}