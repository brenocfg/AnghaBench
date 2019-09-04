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
struct fw_iq_cmd {void* fl0size; void* type_to_iqandstindex; void* alloc_to_len16; void* op_to_vfn; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_iq_params {int /*<<< orphan*/  fl1size; int /*<<< orphan*/  fl0size; int /*<<< orphan*/  iqasynch; int /*<<< orphan*/  type; int /*<<< orphan*/  viid; int /*<<< orphan*/  vfn; int /*<<< orphan*/  pfn; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_iq_cmd*,int /*<<< orphan*/ ,void*,void (*) (struct csio_hw*,struct csio_mb*),int) ; 
 int FW_CMD_EXEC_F ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int /*<<< orphan*/  FW_IQ_CMD ; 
 int FW_IQ_CMD_ALLOC_F ; 
 int FW_IQ_CMD_IQASYNCH_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_PFN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_TYPE_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_VFN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_VIID_V (int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 void* htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_mb_iq_alloc(struct csio_hw *hw, struct csio_mb *mbp, void *priv,
		 uint32_t mb_tmo, struct csio_iq_params *iq_params,
		 void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct fw_iq_cmd *cmdp = (struct fw_iq_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_tmo, priv, cbfn, 1);

	cmdp->op_to_vfn = htonl(FW_CMD_OP_V(FW_IQ_CMD)		|
				FW_CMD_REQUEST_F | FW_CMD_EXEC_F	|
				FW_IQ_CMD_PFN_V(iq_params->pfn)	|
				FW_IQ_CMD_VFN_V(iq_params->vfn));

	cmdp->alloc_to_len16 = htonl(FW_IQ_CMD_ALLOC_F		|
				FW_CMD_LEN16_V(sizeof(*cmdp) / 16));

	cmdp->type_to_iqandstindex = htonl(
				FW_IQ_CMD_VIID_V(iq_params->viid)	|
				FW_IQ_CMD_TYPE_V(iq_params->type)	|
				FW_IQ_CMD_IQASYNCH_V(iq_params->iqasynch));

	cmdp->fl0size = htons(iq_params->fl0size);
	cmdp->fl0size = htons(iq_params->fl1size);

}