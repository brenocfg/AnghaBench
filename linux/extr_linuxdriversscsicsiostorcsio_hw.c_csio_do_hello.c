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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct csio_mb {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; int /*<<< orphan*/  pfn; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  state_str ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;
typedef  enum csio_dev_state { ____Placeholder_csio_dev_state } csio_dev_state ;

/* Variables and functions */
#define  CSIO_DEV_STATE_ERR 130 
#define  CSIO_DEV_STATE_INIT 129 
#define  CSIO_DEV_STATE_UNINIT 128 
 int /*<<< orphan*/  CSIO_HWF_MASTER ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_MASTER_MAY ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int FW_CMD_HELLO_RETRIES ; 
 int FW_CMD_HELLO_TIMEOUT ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCIE_FW_A ; 
 int PCIE_FW_ERR_F ; 
 int PCIE_FW_INIT_F ; 
 int /*<<< orphan*/  PCIE_FW_MASTER_G (int) ; 
 int /*<<< orphan*/  PCIE_FW_MASTER_M ; 
 int PCIE_FW_MASTER_VLD_F ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,int) ; 
 int /*<<< orphan*/  csio_info (struct csio_hw*,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  csio_mb_hello (struct csio_hw*,struct csio_mb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_mb_process_hello_rsp (struct csio_hw*,struct csio_mb*,int*,int*,int /*<<< orphan*/ *) ; 
 int csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  n_err_nomem ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int
csio_do_hello(struct csio_hw *hw, enum csio_dev_state *state)
{
	struct csio_mb	*mbp;
	int	rv = 0;
	enum fw_retval retval;
	uint8_t mpfn;
	char state_str[16];
	int retries = FW_CMD_HELLO_RETRIES;

	memset(state_str, 0, sizeof(state_str));

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		rv = -ENOMEM;
		CSIO_INC_STATS(hw, n_err_nomem);
		goto out;
	}

retry:
	csio_mb_hello(hw, mbp, CSIO_MB_DEFAULT_TMO, hw->pfn,
		      hw->pfn, CSIO_MASTER_MAY, NULL);

	rv = csio_mb_issue(hw, mbp);
	if (rv) {
		csio_err(hw, "failed to issue HELLO cmd. ret:%d.\n", rv);
		goto out_free_mb;
	}

	csio_mb_process_hello_rsp(hw, mbp, &retval, state, &mpfn);
	if (retval != FW_SUCCESS) {
		csio_err(hw, "HELLO cmd failed with ret: %d\n", retval);
		rv = -EINVAL;
		goto out_free_mb;
	}

	/* Firmware has designated us to be master */
	if (hw->pfn == mpfn) {
		hw->flags |= CSIO_HWF_MASTER;
	} else if (*state == CSIO_DEV_STATE_UNINIT) {
		/*
		 * If we're not the Master PF then we need to wait around for
		 * the Master PF Driver to finish setting up the adapter.
		 *
		 * Note that we also do this wait if we're a non-Master-capable
		 * PF and there is no current Master PF; a Master PF may show up
		 * momentarily and we wouldn't want to fail pointlessly.  (This
		 * can happen when an OS loads lots of different drivers rapidly
		 * at the same time). In this case, the Master PF returned by
		 * the firmware will be PCIE_FW_MASTER_MASK so the test below
		 * will work ...
		 */

		int waiting = FW_CMD_HELLO_TIMEOUT;

		/*
		 * Wait for the firmware to either indicate an error or
		 * initialized state.  If we see either of these we bail out
		 * and report the issue to the caller.  If we exhaust the
		 * "hello timeout" and we haven't exhausted our retries, try
		 * again.  Otherwise bail with a timeout error.
		 */
		for (;;) {
			uint32_t pcie_fw;

			spin_unlock_irq(&hw->lock);
			msleep(50);
			spin_lock_irq(&hw->lock);
			waiting -= 50;

			/*
			 * If neither Error nor Initialialized are indicated
			 * by the firmware keep waiting till we exaust our
			 * timeout ... and then retry if we haven't exhausted
			 * our retries ...
			 */
			pcie_fw = csio_rd_reg32(hw, PCIE_FW_A);
			if (!(pcie_fw & (PCIE_FW_ERR_F|PCIE_FW_INIT_F))) {
				if (waiting <= 0) {
					if (retries-- > 0)
						goto retry;

					rv = -ETIMEDOUT;
					break;
				}
				continue;
			}

			/*
			 * We either have an Error or Initialized condition
			 * report errors preferentially.
			 */
			if (state) {
				if (pcie_fw & PCIE_FW_ERR_F) {
					*state = CSIO_DEV_STATE_ERR;
					rv = -ETIMEDOUT;
				} else if (pcie_fw & PCIE_FW_INIT_F)
					*state = CSIO_DEV_STATE_INIT;
			}

			/*
			 * If we arrived before a Master PF was selected and
			 * there's not a valid Master PF, grab its identity
			 * for our caller.
			 */
			if (mpfn == PCIE_FW_MASTER_M &&
			    (pcie_fw & PCIE_FW_MASTER_VLD_F))
				mpfn = PCIE_FW_MASTER_G(pcie_fw);
			break;
		}
		hw->flags &= ~CSIO_HWF_MASTER;
	}

	switch (*state) {
	case CSIO_DEV_STATE_UNINIT:
		strcpy(state_str, "Initializing");
		break;
	case CSIO_DEV_STATE_INIT:
		strcpy(state_str, "Initialized");
		break;
	case CSIO_DEV_STATE_ERR:
		strcpy(state_str, "Error");
		break;
	default:
		strcpy(state_str, "Unknown");
		break;
	}

	if (hw->pfn == mpfn)
		csio_info(hw, "PF: %d, Coming up as MASTER, HW state: %s\n",
			hw->pfn, state_str);
	else
		csio_info(hw,
		    "PF: %d, Coming up as SLAVE, Master PF: %d, HW state: %s\n",
		    hw->pfn, mpfn, state_str);

out_free_mb:
	mempool_free(mbp, hw->mb_mempool);
out:
	return rv;
}