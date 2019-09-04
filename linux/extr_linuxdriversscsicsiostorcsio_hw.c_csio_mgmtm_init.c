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
struct csio_mgmtm {struct csio_hw* hw; int /*<<< orphan*/  cbfn_q; int /*<<< orphan*/  active_q; int /*<<< orphan*/  mgmt_timer; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_mgmt_tmo_handler ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csio_mgmtm_init(struct csio_mgmtm *mgmtm, struct csio_hw *hw)
{
	timer_setup(&mgmtm->mgmt_timer, csio_mgmt_tmo_handler, 0);

	INIT_LIST_HEAD(&mgmtm->active_q);
	INIT_LIST_HEAD(&mgmtm->cbfn_q);

	mgmtm->hw = hw;
	/*mgmtm->iq_idx = hw->fwevt_iq_idx;*/

	return 0;
}