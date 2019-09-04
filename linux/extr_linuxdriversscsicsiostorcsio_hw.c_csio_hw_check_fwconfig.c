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
typedef  int u32 ;
struct csio_mb {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; int /*<<< orphan*/  pfn; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_CF ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,...) ; 
 scalar_t__ csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_mb_params (struct csio_hw*,struct csio_mb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_mb_process_read_params_rsp (struct csio_hw*,struct csio_mb*,int*,int /*<<< orphan*/ ,int*) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 

__attribute__((used)) static int
csio_hw_check_fwconfig(struct csio_hw *hw, u32 *param)
{
	struct csio_mb	*mbp;
	enum fw_retval retval;
	u32 _param[1];

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}

	/*
	 * Find out whether we're dealing with a version of
	 * the firmware which has configuration file support.
	 */
	_param[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_CF));

	csio_mb_params(hw, mbp, CSIO_MB_DEFAULT_TMO, hw->pfn, 0,
		       ARRAY_SIZE(_param), _param, NULL, false, NULL);
	if (csio_mb_issue(hw, mbp)) {
		csio_err(hw, "Issue of FW_PARAMS_CMD(read) failed!\n");
		mempool_free(mbp, hw->mb_mempool);
		return -EINVAL;
	}

	csio_mb_process_read_params_rsp(hw, mbp, &retval,
			ARRAY_SIZE(_param), _param);
	if (retval != FW_SUCCESS) {
		csio_err(hw, "FW_PARAMS_CMD(read) failed with ret:0x%x!\n",
				retval);
		mempool_free(mbp, hw->mb_mempool);
		return -EINVAL;
	}

	mempool_free(mbp, hw->mb_mempool);
	*param = _param[0];

	return 0;
}