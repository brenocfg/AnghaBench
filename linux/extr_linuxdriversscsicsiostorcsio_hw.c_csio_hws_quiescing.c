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
struct csio_hw {int prev_evt; int cur_evt; int /*<<< orphan*/  sm; int /*<<< orphan*/  evtflag; } ;
typedef  enum csio_hw_ev { ____Placeholder_csio_hw_ev } csio_hw_ev ;

/* Variables and functions */
#define  CSIO_HWE_FW_DLOAD 133 
#define  CSIO_HWE_HBA_RESET 132 
 int /*<<< orphan*/  CSIO_HWE_HBA_RESET_DONE ; 
#define  CSIO_HWE_PCIERR_DETECTED 131 
#define  CSIO_HWE_PCI_REMOVE 130 
#define  CSIO_HWE_QUIESCED 129 
#define  CSIO_HWE_SUSPEND 128 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_LN_NOTIFY_HWREMOVE ; 
 int /*<<< orphan*/  CSIO_LN_NOTIFY_HWRESET ; 
 int /*<<< orphan*/  csio_do_bye (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_do_reset (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_hws_pcierr ; 
 int /*<<< orphan*/  csio_hws_quiesced ; 
 int /*<<< orphan*/  csio_hws_removing ; 
 int /*<<< orphan*/  csio_hws_resetting ; 
 int /*<<< orphan*/  csio_notify_lnodes (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_destroy_queues (struct csio_hw*,int) ; 
 int /*<<< orphan*/ * n_evt_sm ; 
 int /*<<< orphan*/  n_evt_unexp ; 

__attribute__((used)) static void
csio_hws_quiescing(struct csio_hw *hw, enum csio_hw_ev evt)
{
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	switch (evt) {
	case CSIO_HWE_QUIESCED:
		switch (hw->evtflag) {
		case CSIO_HWE_FW_DLOAD:
			csio_set_state(&hw->sm, csio_hws_resetting);
			/* Download firmware */
			/* Fall through */

		case CSIO_HWE_HBA_RESET:
			csio_set_state(&hw->sm, csio_hws_resetting);
			/* Start reset of the HBA */
			csio_notify_lnodes(hw, CSIO_LN_NOTIFY_HWRESET);
			csio_wr_destroy_queues(hw, false);
			csio_do_reset(hw, false);
			csio_post_event(&hw->sm, CSIO_HWE_HBA_RESET_DONE);
			break;

		case CSIO_HWE_PCI_REMOVE:
			csio_set_state(&hw->sm, csio_hws_removing);
			csio_notify_lnodes(hw, CSIO_LN_NOTIFY_HWREMOVE);
			csio_wr_destroy_queues(hw, true);
			/* Now send the bye command */
			csio_do_bye(hw);
			break;

		case CSIO_HWE_SUSPEND:
			csio_set_state(&hw->sm, csio_hws_quiesced);
			break;

		case CSIO_HWE_PCIERR_DETECTED:
			csio_set_state(&hw->sm, csio_hws_pcierr);
			csio_wr_destroy_queues(hw, false);
			break;

		default:
			CSIO_INC_STATS(hw, n_evt_unexp);
			break;

		}
		break;

	default:
		CSIO_INC_STATS(hw, n_evt_unexp);
		break;
	}
}