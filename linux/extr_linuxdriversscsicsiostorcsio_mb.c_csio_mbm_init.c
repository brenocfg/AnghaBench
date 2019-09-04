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
struct csio_mbm {int /*<<< orphan*/  cbfn_q; int /*<<< orphan*/  req_q; int /*<<< orphan*/  timer; struct csio_hw* hw; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_set_mb_intr_idx (struct csio_mbm*,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,void (*) (struct timer_list*),int /*<<< orphan*/ ) ; 

int
csio_mbm_init(struct csio_mbm *mbm, struct csio_hw *hw,
	      void (*timer_fn)(struct timer_list *))
{
	mbm->hw = hw;
	timer_setup(&mbm->timer, timer_fn, 0);

	INIT_LIST_HEAD(&mbm->req_q);
	INIT_LIST_HEAD(&mbm->cbfn_q);
	csio_set_mb_intr_idx(mbm, -1);

	return 0;
}