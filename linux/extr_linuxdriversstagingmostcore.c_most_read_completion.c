#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* comp; scalar_t__ refs; } ;
struct TYPE_6__ {TYPE_1__* comp; scalar_t__ refs; } ;
struct most_channel {int is_starving; TYPE_4__ pipe1; TYPE_2__ pipe0; int /*<<< orphan*/  mbo_nq_level; scalar_t__ is_poisoned; } ;
struct mbo {scalar_t__ status; struct most_channel* context; } ;
struct TYPE_7__ {scalar_t__ (* rx_completion ) (struct mbo*) ;} ;
struct TYPE_5__ {scalar_t__ (* rx_completion ) (struct mbo*) ;} ;

/* Variables and functions */
 scalar_t__ MBO_E_CLOSE ; 
 scalar_t__ MBO_E_INVAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_sub_and_test (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  most_put_mbo (struct mbo*) ; 
 int /*<<< orphan*/  nq_hdm_mbo (struct mbo*) ; 
 scalar_t__ stub1 (struct mbo*) ; 
 scalar_t__ stub2 (struct mbo*) ; 
 int /*<<< orphan*/  trash_mbo (struct mbo*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void most_read_completion(struct mbo *mbo)
{
	struct most_channel *c = mbo->context;

	if (unlikely(c->is_poisoned || (mbo->status == MBO_E_CLOSE))) {
		trash_mbo(mbo);
		return;
	}

	if (mbo->status == MBO_E_INVAL) {
		nq_hdm_mbo(mbo);
		atomic_inc(&c->mbo_nq_level);
		return;
	}

	if (atomic_sub_and_test(1, &c->mbo_nq_level))
		c->is_starving = 1;

	if (c->pipe0.refs && c->pipe0.comp->rx_completion &&
	    c->pipe0.comp->rx_completion(mbo) == 0)
		return;

	if (c->pipe1.refs && c->pipe1.comp->rx_completion &&
	    c->pipe1.comp->rx_completion(mbo) == 0)
		return;

	most_put_mbo(mbo);
}