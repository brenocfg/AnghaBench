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
struct csio_mb {int dummy; } ;
struct csio_hw {scalar_t__ fw_state; int /*<<< orphan*/  mb_mempool; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;

/* Variables and functions */
 scalar_t__ CSIO_DEV_STATE_INIT ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,...) ; 
 int csio_hw_validate_caps (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_mb_caps_config (struct csio_hw*,struct csio_mb*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *) ; 
 int csio_mb_fw_retval (struct csio_mb*) ; 
 scalar_t__ csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 

__attribute__((used)) static int
csio_config_device_caps(struct csio_hw *hw)
{
	struct csio_mb	*mbp;
	enum fw_retval retval;
	int rv = -EINVAL;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}

	/* Get device capabilities */
	csio_mb_caps_config(hw, mbp, CSIO_MB_DEFAULT_TMO, 0, 0, 0, 0, NULL);

	if (csio_mb_issue(hw, mbp)) {
		csio_err(hw, "Issue of FW_CAPS_CONFIG_CMD(r) failed!\n");
		goto out;
	}

	retval = csio_mb_fw_retval(mbp);
	if (retval != FW_SUCCESS) {
		csio_err(hw, "FW_CAPS_CONFIG_CMD(r) returned %d!\n", retval);
		goto out;
	}

	/* Validate device capabilities */
	rv = csio_hw_validate_caps(hw, mbp);
	if (rv != 0)
		goto out;

	/* Don't config device capabilities if already configured */
	if (hw->fw_state == CSIO_DEV_STATE_INIT) {
		rv = 0;
		goto out;
	}

	/* Write back desired device capabilities */
	csio_mb_caps_config(hw, mbp, CSIO_MB_DEFAULT_TMO, true, true,
			    false, true, NULL);

	if (csio_mb_issue(hw, mbp)) {
		csio_err(hw, "Issue of FW_CAPS_CONFIG_CMD(w) failed!\n");
		goto out;
	}

	retval = csio_mb_fw_retval(mbp);
	if (retval != FW_SUCCESS) {
		csio_err(hw, "FW_CAPS_CONFIG_CMD(w) returned %d!\n", retval);
		goto out;
	}

	rv = 0;
out:
	mempool_free(mbp, hw->mb_mempool);
	return rv;
}