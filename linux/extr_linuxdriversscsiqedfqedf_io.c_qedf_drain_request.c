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
struct qedf_ctx {int /*<<< orphan*/  flags; int /*<<< orphan*/  cdev; int /*<<< orphan*/  dbg_ctx; } ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* drain ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_DRAIN_ACTIVE ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_2__* qed_ops ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedf_drain_request(struct qedf_ctx *qedf)
{
	if (test_bit(QEDF_DRAIN_ACTIVE, &qedf->flags)) {
		QEDF_ERR(&(qedf->dbg_ctx), "MCP drain already active.\n");
		return;
	}

	/* Set bit to return all queuecommand requests as busy */
	set_bit(QEDF_DRAIN_ACTIVE, &qedf->flags);

	/* Call qed drain request for function. Should be synchronous */
	qed_ops->common->drain(qedf->cdev);

	/* Settle time for CQEs to be returned */
	msleep(100);

	/* Unplug and continue */
	clear_bit(QEDF_DRAIN_ACTIVE, &qedf->flags);
}