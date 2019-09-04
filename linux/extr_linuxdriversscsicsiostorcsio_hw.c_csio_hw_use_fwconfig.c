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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct fw_caps_config_cmd {void* cfvalid_to_len16; void* op_to_write; int /*<<< orphan*/  cfcsum; int /*<<< orphan*/  finicsum; int /*<<< orphan*/  finiver; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int /*<<< orphan*/  flags; int /*<<< orphan*/  mb_mempool; int /*<<< orphan*/  sm; TYPE_1__* chip_ops; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {unsigned int (* chip_flash_cfg_addr ) (struct csio_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_HWE_INIT ; 
 int /*<<< orphan*/  CSIO_HWF_USING_SOFT_PARAMS ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_caps_config_cmd*,int /*<<< orphan*/ ,struct csio_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_CAPS_CONFIG_CMD ; 
 int FW_CAPS_CONFIG_CMD_CFVALID_F ; 
 int FW_CAPS_CONFIG_CMD_MEMADDR64K_CF_V (unsigned int) ; 
 int FW_CAPS_CONFIG_CMD_MEMTYPE_CF_V (unsigned int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int FW_LEN16 (struct fw_caps_config_cmd) ; 
 unsigned int FW_MEMTYPE_CF_FLASH ; 
 unsigned int FW_PARAMS_PARAM_Y_G (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_Z_G (int /*<<< orphan*/ ) ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,int) ; 
 int csio_do_reset (struct csio_hw*,int) ; 
 int csio_get_device_params (struct csio_hw*) ; 
 int csio_hw_flash_config (struct csio_hw*,int /*<<< orphan*/ *,char*) ; 
 int csio_hw_validate_caps (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_info (struct csio_hw*,char*,char*,scalar_t__,scalar_t__) ; 
 int csio_mb_fw_retval (struct csio_mb*) ; 
 scalar_t__ csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_warn (struct csio_hw*,char*,int,...) ; 
 int /*<<< orphan*/  csio_wr_sge_init (struct csio_hw*) ; 
 void* htonl (int) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 unsigned int stub1 (struct csio_hw*) ; 

__attribute__((used)) static int
csio_hw_use_fwconfig(struct csio_hw *hw, int reset, u32 *fw_cfg_param)
{
	struct csio_mb	*mbp = NULL;
	struct fw_caps_config_cmd *caps_cmd;
	unsigned int mtype, maddr;
	int rv = -EINVAL;
	uint32_t finiver = 0, finicsum = 0, cfcsum = 0;
	char path[64];
	char *config_name = NULL;

	/*
	 * Reset device if necessary
	 */
	if (reset) {
		rv = csio_do_reset(hw, true);
		if (rv != 0)
			goto bye;
	}

	/*
	 * If we have a configuration file in host ,
	 * then use that.  Otherwise, use the configuration file stored
	 * in the HW flash ...
	 */
	spin_unlock_irq(&hw->lock);
	rv = csio_hw_flash_config(hw, fw_cfg_param, path);
	spin_lock_irq(&hw->lock);
	if (rv != 0) {
		/*
		 * config file was not found. Use default
		 * config file from flash.
		 */
		config_name = "On FLASH";
		mtype = FW_MEMTYPE_CF_FLASH;
		maddr = hw->chip_ops->chip_flash_cfg_addr(hw);
	} else {
		config_name = path;
		mtype = FW_PARAMS_PARAM_Y_G(*fw_cfg_param);
		maddr = FW_PARAMS_PARAM_Z_G(*fw_cfg_param) << 16;
	}

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}
	/*
	 * Tell the firmware to process the indicated Configuration File.
	 * If there are no errors and the caller has provided return value
	 * pointers for the [fini] section version, checksum and computed
	 * checksum, pass those back to the caller.
	 */
	caps_cmd = (struct fw_caps_config_cmd *)(mbp->mb);
	CSIO_INIT_MBP(mbp, caps_cmd, CSIO_MB_DEFAULT_TMO, hw, NULL, 1);
	caps_cmd->op_to_write =
		htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
		      FW_CMD_REQUEST_F |
		      FW_CMD_READ_F);
	caps_cmd->cfvalid_to_len16 =
		htonl(FW_CAPS_CONFIG_CMD_CFVALID_F |
		      FW_CAPS_CONFIG_CMD_MEMTYPE_CF_V(mtype) |
		      FW_CAPS_CONFIG_CMD_MEMADDR64K_CF_V(maddr >> 16) |
		      FW_LEN16(*caps_cmd));

	if (csio_mb_issue(hw, mbp)) {
		rv = -EINVAL;
		goto bye;
	}

	rv = csio_mb_fw_retval(mbp);
	 /* If the CAPS_CONFIG failed with an ENOENT (for a Firmware
	  * Configuration File in FLASH), our last gasp effort is to use the
	  * Firmware Configuration File which is embedded in the
	  * firmware.  A very few early versions of the firmware didn't
	  * have one embedded but we can ignore those.
	  */
	if (rv == ENOENT) {
		CSIO_INIT_MBP(mbp, caps_cmd, CSIO_MB_DEFAULT_TMO, hw, NULL, 1);
		caps_cmd->op_to_write = htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
					      FW_CMD_REQUEST_F |
					      FW_CMD_READ_F);
		caps_cmd->cfvalid_to_len16 = htonl(FW_LEN16(*caps_cmd));

		if (csio_mb_issue(hw, mbp)) {
			rv = -EINVAL;
			goto bye;
		}

		rv = csio_mb_fw_retval(mbp);
		config_name = "Firmware Default";
	}
	if (rv != FW_SUCCESS)
		goto bye;

	finiver = ntohl(caps_cmd->finiver);
	finicsum = ntohl(caps_cmd->finicsum);
	cfcsum = ntohl(caps_cmd->cfcsum);

	/*
	 * And now tell the firmware to use the configuration we just loaded.
	 */
	caps_cmd->op_to_write =
		htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
		      FW_CMD_REQUEST_F |
		      FW_CMD_WRITE_F);
	caps_cmd->cfvalid_to_len16 = htonl(FW_LEN16(*caps_cmd));

	if (csio_mb_issue(hw, mbp)) {
		rv = -EINVAL;
		goto bye;
	}

	rv = csio_mb_fw_retval(mbp);
	if (rv != FW_SUCCESS) {
		csio_dbg(hw, "FW_CAPS_CONFIG_CMD returned %d!\n", rv);
		goto bye;
	}

	if (finicsum != cfcsum) {
		csio_warn(hw,
		      "Config File checksum mismatch: csum=%#x, computed=%#x\n",
		      finicsum, cfcsum);
	}

	/* Validate device capabilities */
	rv = csio_hw_validate_caps(hw, mbp);
	if (rv != 0)
		goto bye;

	mempool_free(mbp, hw->mb_mempool);
	mbp = NULL;

	/*
	 * Note that we're operating with parameters
	 * not supplied by the driver, rather than from hard-wired
	 * initialization constants buried in the driver.
	 */
	hw->flags |= CSIO_HWF_USING_SOFT_PARAMS;

	/* device parameters */
	rv = csio_get_device_params(hw);
	if (rv != 0)
		goto bye;

	/* Configure SGE */
	csio_wr_sge_init(hw);

	/*
	 * And finally tell the firmware to initialize itself using the
	 * parameters from the Configuration File.
	 */
	/* Post event to notify completion of configuration */
	csio_post_event(&hw->sm, CSIO_HWE_INIT);

	csio_info(hw, "Successfully configure using Firmware "
		  "Configuration File %s, version %#x, computed checksum %#x\n",
		  config_name, finiver, cfcsum);
	return 0;

	/*
	 * Something bad happened.  Return the error ...
	 */
bye:
	if (mbp)
		mempool_free(mbp, hw->mb_mempool);
	hw->flags &= ~CSIO_HWF_USING_SOFT_PARAMS;
	csio_warn(hw, "Configuration file error %d\n", rv);
	return rv;
}