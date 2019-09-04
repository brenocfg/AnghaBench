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
struct csio_hw {int prev_evt; int cur_evt; int /*<<< orphan*/  sm; } ;
typedef  enum csio_hw_ev { ____Placeholder_csio_hw_ev } csio_hw_ev ;

/* Variables and functions */
#define  CSIO_HWE_FATAL 131 
#define  CSIO_HWE_INIT 130 
#define  CSIO_HWE_INIT_DONE 129 
#define  CSIO_HWE_PCI_REMOVE 128 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_LN_NOTIFY_HWREADY ; 
 int /*<<< orphan*/  csio_do_bye (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_initialize (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hws_initializing ; 
 int /*<<< orphan*/  csio_hws_ready ; 
 int /*<<< orphan*/  csio_hws_uninit ; 
 int /*<<< orphan*/  csio_notify_lnodes (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * n_evt_sm ; 
 int /*<<< orphan*/  n_evt_unexp ; 

__attribute__((used)) static void
csio_hws_configuring(struct csio_hw *hw, enum csio_hw_ev evt)
{
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	switch (evt) {
	case CSIO_HWE_INIT:
		csio_set_state(&hw->sm, csio_hws_initializing);
		csio_hw_initialize(hw);
		break;

	case CSIO_HWE_INIT_DONE:
		csio_set_state(&hw->sm, csio_hws_ready);
		/* Fan out event to all lnode SMs */
		csio_notify_lnodes(hw, CSIO_LN_NOTIFY_HWREADY);
		break;

	case CSIO_HWE_FATAL:
		csio_set_state(&hw->sm, csio_hws_uninit);
		break;

	case CSIO_HWE_PCI_REMOVE:
		csio_do_bye(hw);
		break;
	default:
		CSIO_INC_STATS(hw, n_evt_unexp);
		break;
	}
}