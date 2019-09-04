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
struct TYPE_2__ {scalar_t__ direction; } ;
struct most_channel {int /*<<< orphan*/  mbo_nq_level; TYPE_1__ cfg; } ;
struct mbo {struct most_channel* context; } ;

/* Variables and functions */
 scalar_t__ MOST_CH_TX ; 
 int /*<<< orphan*/  arm_mbo (struct mbo*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nq_hdm_mbo (struct mbo*) ; 

void most_put_mbo(struct mbo *mbo)
{
	struct most_channel *c = mbo->context;

	if (c->cfg.direction == MOST_CH_TX) {
		arm_mbo(mbo);
		return;
	}
	nq_hdm_mbo(mbo);
	atomic_inc(&c->mbo_nq_level);
}