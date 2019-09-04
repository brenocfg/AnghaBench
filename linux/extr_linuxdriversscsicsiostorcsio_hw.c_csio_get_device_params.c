#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct csio_wrm {void* fw_iq_start; void* fw_eq_start; } ;
struct csio_mb {int dummy; } ;
struct TYPE_3__ {void* cclk; } ;
struct csio_hw {int port_vec; int flags; int num_pports; int /*<<< orphan*/  mb_mempool; TYPE_2__* pport; void* cfg_neq; void* cfg_niq; TYPE_1__ vpd; int /*<<< orphan*/  pfn; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;
struct TYPE_4__ {int portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  CCLK ; 
 int CSIO_HWF_USING_SOFT_PARAMS ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int CSIO_MAX_PPORTS ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EQ_END ; 
 int /*<<< orphan*/  EQ_START ; 
 void* FW_PARAM_DEV (int /*<<< orphan*/ ) ; 
 void* FW_PARAM_PFVF (int /*<<< orphan*/ ) ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IQFLINT_END ; 
 int /*<<< orphan*/  IQFLINT_START ; 
 int /*<<< orphan*/  PORTVEC ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,int,...) ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,...) ; 
 struct csio_wrm* csio_hw_to_wrm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_is_hw_master (struct csio_hw*) ; 
 scalar_t__ csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_mb_params (struct csio_hw*,struct csio_mb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_mb_process_read_params_rsp (struct csio_hw*,struct csio_mb*,int*,int /*<<< orphan*/ ,void**) ; 
 int csio_port_mask ; 
 int hweight32 (int) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 

__attribute__((used)) static int
csio_get_device_params(struct csio_hw *hw)
{
	struct csio_wrm *wrm	= csio_hw_to_wrm(hw);
	struct csio_mb	*mbp;
	enum fw_retval retval;
	u32 param[6];
	int i, j = 0;

	/* Initialize portids to -1 */
	for (i = 0; i < CSIO_MAX_PPORTS; i++)
		hw->pport[i].portid = -1;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}

	/* Get port vec information. */
	param[0] = FW_PARAM_DEV(PORTVEC);

	/* Get Core clock. */
	param[1] = FW_PARAM_DEV(CCLK);

	/* Get EQ id start and end. */
	param[2] = FW_PARAM_PFVF(EQ_START);
	param[3] = FW_PARAM_PFVF(EQ_END);

	/* Get IQ id start and end. */
	param[4] = FW_PARAM_PFVF(IQFLINT_START);
	param[5] = FW_PARAM_PFVF(IQFLINT_END);

	csio_mb_params(hw, mbp, CSIO_MB_DEFAULT_TMO, hw->pfn, 0,
		       ARRAY_SIZE(param), param, NULL, false, NULL);
	if (csio_mb_issue(hw, mbp)) {
		csio_err(hw, "Issue of FW_PARAMS_CMD(read) failed!\n");
		mempool_free(mbp, hw->mb_mempool);
		return -EINVAL;
	}

	csio_mb_process_read_params_rsp(hw, mbp, &retval,
			ARRAY_SIZE(param), param);
	if (retval != FW_SUCCESS) {
		csio_err(hw, "FW_PARAMS_CMD(read) failed with ret:0x%x!\n",
				retval);
		mempool_free(mbp, hw->mb_mempool);
		return -EINVAL;
	}

	/* cache the information. */
	hw->port_vec = param[0];
	hw->vpd.cclk = param[1];
	wrm->fw_eq_start = param[2];
	wrm->fw_iq_start = param[4];

	/* Using FW configured max iqs & eqs */
	if ((hw->flags & CSIO_HWF_USING_SOFT_PARAMS) ||
		!csio_is_hw_master(hw)) {
		hw->cfg_niq = param[5] - param[4] + 1;
		hw->cfg_neq = param[3] - param[2] + 1;
		csio_dbg(hw, "Using fwconfig max niqs %d neqs %d\n",
			hw->cfg_niq, hw->cfg_neq);
	}

	hw->port_vec &= csio_port_mask;

	hw->num_pports	= hweight32(hw->port_vec);

	csio_dbg(hw, "Port vector: 0x%x, #ports: %d\n",
		    hw->port_vec, hw->num_pports);

	for (i = 0; i < hw->num_pports; i++) {
		while ((hw->port_vec & (1 << j)) == 0)
			j++;
		hw->pport[i].portid = j++;
		csio_dbg(hw, "Found Port:%d\n", hw->pport[i].portid);
	}
	mempool_free(mbp, hw->mb_mempool);

	return 0;
}