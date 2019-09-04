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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct fw_params_cmd {void* retval_len16; void* op_to_vfn; TYPE_1__* param; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int dummy; } ;
typedef  void* __be32 ;
struct TYPE_2__ {void* mnem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_params_cmd*,unsigned int,struct csio_hw*,void (*) (struct csio_hw*,struct csio_mb*),int) ; 
 unsigned int FW_CMD_LEN16_V (int) ; 
 unsigned int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 unsigned int FW_CMD_READ_F ; 
 unsigned int FW_CMD_REQUEST_F ; 
 unsigned int FW_CMD_WRITE_F ; 
 int /*<<< orphan*/  FW_PARAMS_CMD ; 
 unsigned int FW_PARAMS_CMD_PFN_V (unsigned int) ; 
 unsigned int FW_PARAMS_CMD_VFN_V (unsigned int) ; 
 void* htonl (unsigned int) ; 

void
csio_mb_params(struct csio_hw *hw, struct csio_mb *mbp, uint32_t tmo,
	       unsigned int pf, unsigned int vf, unsigned int nparams,
	       const u32 *params, u32 *val, bool wr,
	       void (*cbfn)(struct csio_hw *, struct csio_mb *))
{
	uint32_t i;
	uint32_t temp_params = 0, temp_val = 0;
	struct fw_params_cmd *cmdp = (struct fw_params_cmd *)(mbp->mb);
	__be32 *p = &cmdp->param[0].mnem;

	CSIO_INIT_MBP(mbp, cmdp, tmo, hw, cbfn, 1);

	cmdp->op_to_vfn = htonl(FW_CMD_OP_V(FW_PARAMS_CMD)		|
				FW_CMD_REQUEST_F			|
				(wr ? FW_CMD_WRITE_F : FW_CMD_READ_F)	|
				FW_PARAMS_CMD_PFN_V(pf)			|
				FW_PARAMS_CMD_VFN_V(vf));
	cmdp->retval_len16 = htonl(FW_CMD_LEN16_V(sizeof(*cmdp) / 16));

	/* Write Params */
	if (wr) {
		while (nparams--) {
			temp_params = *params++;
			temp_val = *val++;

			*p++ = htonl(temp_params);
			*p++ = htonl(temp_val);
		}
	} else {
		for (i = 0; i < nparams; i++, p += 2) {
			temp_params = *params++;
			*p = htonl(temp_params);
		}
	}

}