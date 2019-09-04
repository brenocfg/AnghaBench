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
typedef  int /*<<< orphan*/  u32 ;
struct srr {scalar_t__ dqp_index; } ;
struct bdc {int /*<<< orphan*/  dev; struct srr srr; } ;

/* Variables and functions */
 scalar_t__ NUM_SR_ENTRIES ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void srr_dqp_index_advc(struct bdc *bdc, u32 srr_num)
{
	struct srr *srr;

	srr = &bdc->srr;
	dev_dbg_ratelimited(bdc->dev, "srr->dqp_index:%d\n", srr->dqp_index);
	srr->dqp_index++;
	/* rollback to 0 if we are past the last */
	if (srr->dqp_index == NUM_SR_ENTRIES)
		srr->dqp_index = 0;
}