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
struct TYPE_2__ {int /*<<< orphan*/  n_reset_start; } ;
struct csio_hw {scalar_t__ rst_retries; TYPE_1__ stats; int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_HWE_HBA_RESET ; 
 scalar_t__ CSIO_MAX_RESET_RETRIES ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_is_hw_master (struct csio_hw*) ; 
 scalar_t__ csio_is_hw_ready (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 

int
csio_hw_reset(struct csio_hw *hw)
{
	if (!csio_is_hw_master(hw))
		return -EPERM;

	if (hw->rst_retries >= CSIO_MAX_RESET_RETRIES) {
		csio_dbg(hw, "Max hw reset attempts reached..");
		return -EINVAL;
	}

	hw->rst_retries++;
	csio_post_event(&hw->sm, CSIO_HWE_HBA_RESET);

	if (csio_is_hw_ready(hw)) {
		hw->rst_retries = 0;
		hw->stats.n_reset_start = jiffies_to_msecs(jiffies);
		return 0;
	} else
		return -EINVAL;
}