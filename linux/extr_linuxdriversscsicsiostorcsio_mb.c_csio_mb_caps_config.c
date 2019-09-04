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
typedef  int /*<<< orphan*/  uint32_t ;
struct fw_caps_config_cmd {int /*<<< orphan*/  fcoecaps; void* cfvalid_to_len16; void* op_to_write; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_caps_config_cmd*,int /*<<< orphan*/ ,struct csio_hw*,void (*) (struct csio_hw*,struct csio_mb*),int) ; 
 int /*<<< orphan*/  FW_CAPS_CONFIG_CMD ; 
 int /*<<< orphan*/  FW_CAPS_CONFIG_FCOE_CTRL_OFLD ; 
 int /*<<< orphan*/  FW_CAPS_CONFIG_FCOE_INITIATOR ; 
 int /*<<< orphan*/  FW_CAPS_CONFIG_FCOE_TARGET ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

void
csio_mb_caps_config(struct csio_hw *hw, struct csio_mb *mbp, uint32_t tmo,
		    bool wr, bool init, bool tgt, bool cofld,
		    void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct fw_caps_config_cmd *cmdp =
				(struct fw_caps_config_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, tmo, hw, cbfn, wr ? 0 : 1);

	cmdp->op_to_write = htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
				  FW_CMD_REQUEST_F		|
				  (wr ? FW_CMD_WRITE_F : FW_CMD_READ_F));
	cmdp->cfvalid_to_len16 = htonl(FW_CMD_LEN16_V(sizeof(*cmdp) / 16));

	/* Read config */
	if (!wr)
		return;

	/* Write config */
	cmdp->fcoecaps = 0;

	if (cofld)
		cmdp->fcoecaps |= htons(FW_CAPS_CONFIG_FCOE_CTRL_OFLD);
	if (init)
		cmdp->fcoecaps |= htons(FW_CAPS_CONFIG_FCOE_INITIATOR);
	if (tgt)
		cmdp->fcoecaps |= htons(FW_CAPS_CONFIG_FCOE_TARGET);
}