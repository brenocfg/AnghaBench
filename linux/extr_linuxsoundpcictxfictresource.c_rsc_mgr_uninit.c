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
struct rsc_mgr {int type; scalar_t__ amount; scalar_t__ avail; int /*<<< orphan*/ * ctrl_blk; TYPE_2__* hw; int /*<<< orphan*/ * rscs; } ;
struct hw {TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* daio_mgr_put_ctrl_blk ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* amixer_mgr_put_ctrl_blk ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* srcimp_mgr_put_ctrl_blk ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* src_mgr_put_ctrl_blk ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AMIXER 132 
#define  DAIO 131 
 int NUM_RSCTYP ; 
#define  SRC 130 
#define  SRCIMP 129 
#define  SUM 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 

int rsc_mgr_uninit(struct rsc_mgr *mgr)
{
	kfree(mgr->rscs);
	mgr->rscs = NULL;

	if ((NULL != mgr->hw) && (NULL != mgr->ctrl_blk)) {
		switch (mgr->type) {
		case SRC:
			mgr->hw->src_mgr_put_ctrl_blk(mgr->ctrl_blk);
			break;
		case SRCIMP:
			mgr->hw->srcimp_mgr_put_ctrl_blk(mgr->ctrl_blk);
			break;
		case AMIXER:
			mgr->hw->amixer_mgr_put_ctrl_blk(mgr->ctrl_blk);
			break;
		case DAIO:
			mgr->hw->daio_mgr_put_ctrl_blk(mgr->ctrl_blk);
			break;
		case SUM:
			break;
		default:
			dev_err(((struct hw *)mgr->hw)->card->dev,
				"Invalid resource type value %d!\n",
				mgr->type);
			break;
		}

		mgr->hw = mgr->ctrl_blk = NULL;
	}

	mgr->type = NUM_RSCTYP;
	mgr->avail = mgr->amount = 0;

	return 0;
}