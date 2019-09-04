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
struct fw_hello_cmd {void* err_to_clearinit; void* retval_len16; void* op_to_write; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int dummy; } ;
typedef  enum csio_dev_master { ____Placeholder_csio_dev_master } csio_dev_master ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_hello_cmd*,int /*<<< orphan*/ ,struct csio_hw*,void (*) (struct csio_hw*,struct csio_mb*),int) ; 
 int CSIO_MASTER_CANT ; 
 int CSIO_MASTER_MUST ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int /*<<< orphan*/  FW_HELLO_CMD ; 
 int FW_HELLO_CMD_CLEARINIT_F ; 
 int FW_HELLO_CMD_MASTERDIS_V (int) ; 
 int FW_HELLO_CMD_MASTERFORCE_V (int) ; 
 int FW_HELLO_CMD_MBASYNCNOT_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_HELLO_CMD_MBMASTER_M ; 
 int FW_HELLO_CMD_MBMASTER_V (int /*<<< orphan*/ ) ; 
 int FW_HELLO_CMD_STAGE_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_hello_cmd_stage_os ; 
 void* htonl (int) ; 

void
csio_mb_hello(struct csio_hw *hw, struct csio_mb *mbp, uint32_t tmo,
	      uint32_t m_mbox, uint32_t a_mbox, enum csio_dev_master master,
	      void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct fw_hello_cmd *cmdp = (struct fw_hello_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, tmo, hw, cbfn, 1);

	cmdp->op_to_write = htonl(FW_CMD_OP_V(FW_HELLO_CMD) |
				       FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(sizeof(*cmdp) / 16));
	cmdp->err_to_clearinit = htonl(
		FW_HELLO_CMD_MASTERDIS_V(master == CSIO_MASTER_CANT)	|
		FW_HELLO_CMD_MASTERFORCE_V(master == CSIO_MASTER_MUST)	|
		FW_HELLO_CMD_MBMASTER_V(master == CSIO_MASTER_MUST ?
				m_mbox : FW_HELLO_CMD_MBMASTER_M)	|
		FW_HELLO_CMD_MBASYNCNOT_V(a_mbox) |
		FW_HELLO_CMD_STAGE_V(fw_hello_cmd_stage_os) |
		FW_HELLO_CMD_CLEARINIT_F);

}