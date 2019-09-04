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
struct fw_eq_ofld_cmd {void* alloc_to_len16; void* op_to_vfn; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int dummy; } ;
struct csio_eq_params {int /*<<< orphan*/  vfn; int /*<<< orphan*/  pfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_eq_ofld_cmd*,int /*<<< orphan*/ ,void*,void (*) (struct csio_hw*,struct csio_mb*),int) ; 
 int FW_CMD_EXEC_F ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int /*<<< orphan*/  FW_EQ_OFLD_CMD ; 
 int FW_EQ_OFLD_CMD_ALLOC_F ; 
 int FW_EQ_OFLD_CMD_PFN_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_VFN_V (int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 

__attribute__((used)) static void
csio_mb_eq_ofld_alloc(struct csio_hw *hw, struct csio_mb *mbp, void *priv,
		uint32_t mb_tmo, struct csio_eq_params *eq_ofld_params,
		void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct fw_eq_ofld_cmd *cmdp = (struct fw_eq_ofld_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_tmo, priv, cbfn, 1);
	cmdp->op_to_vfn = htonl(FW_CMD_OP_V(FW_EQ_OFLD_CMD)		|
				FW_CMD_REQUEST_F | FW_CMD_EXEC_F	|
				FW_EQ_OFLD_CMD_PFN_V(eq_ofld_params->pfn) |
				FW_EQ_OFLD_CMD_VFN_V(eq_ofld_params->vfn));
	cmdp->alloc_to_len16 = htonl(FW_EQ_OFLD_CMD_ALLOC_F	|
				FW_CMD_LEN16_V(sizeof(*cmdp) / 16));

}