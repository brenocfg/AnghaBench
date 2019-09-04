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
struct csio_hw {scalar_t__ fw_state; int flags; } ;

/* Variables and functions */
 scalar_t__ CSIO_DEV_STATE_INIT ; 
 int CSIO_HWF_USING_SOFT_PARAMS ; 
 scalar_t__ csio_is_hw_master (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_wr_fixup_host_params (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_wr_get_sge (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_wr_set_sge (struct csio_hw*) ; 

void
csio_wr_sge_init(struct csio_hw *hw)
{
	/*
	 * If we are master and chip is not initialized:
	 *    - If we plan to use the config file, we need to fixup some
	 *      host specific registers, and read the rest of the SGE
	 *      configuration.
	 *    - If we dont plan to use the config file, we need to initialize
	 *      SGE entirely, including fixing the host specific registers.
	 * If we are master and chip is initialized, just read and work off of
	 *	the already initialized SGE values.
	 * If we arent the master, we are only allowed to read and work off of
	 *      the already initialized SGE values.
	 *
	 * Therefore, before calling this function, we assume that the master-
	 * ship of the card, state and whether to use config file or not, have
	 * already been decided.
	 */
	if (csio_is_hw_master(hw)) {
		if (hw->fw_state != CSIO_DEV_STATE_INIT)
			csio_wr_fixup_host_params(hw);

		if (hw->flags & CSIO_HWF_USING_SOFT_PARAMS)
			csio_wr_get_sge(hw);
		else
			csio_wr_set_sge(hw);
	} else
		csio_wr_get_sge(hw);
}