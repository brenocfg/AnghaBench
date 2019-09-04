#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  void* u32 ;
struct TYPE_19__ {size_t prod; int comp; } ;
struct TYPE_20__ {int /*<<< orphan*/  lword; TYPE_7__ index; } ;
struct TYPE_16__ {size_t prod; int comp; } ;
struct TYPE_17__ {int /*<<< orphan*/  lword; TYPE_4__ index; } ;
struct TYPE_21__ {TYPE_8__ cmd_rsp_reg; TYPE_6__* cons_block_virt; TYPE_5__ cmd_req_reg; int /*<<< orphan*/  cmd_req_phys; TYPE_3__* descr_block_virt; int /*<<< orphan*/  cmd_rsp_phys; } ;
struct TYPE_18__ {scalar_t__ cmd_rsp; scalar_t__ cmd_req; } ;
struct TYPE_15__ {TYPE_2__* cmd_req; TYPE_1__* cmd_rsp; } ;
struct TYPE_14__ {int /*<<< orphan*/  long_1; void* long_0; } ;
struct TYPE_13__ {int /*<<< orphan*/  long_1; void* long_0; } ;
typedef  TYPE_9__ DFX_board_t ;

/* Variables and functions */
 int DFX_K_HW_TIMEOUT ; 
 int DFX_K_OUTSTATE ; 
 int DFX_K_SUCCESS ; 
 int PI_ALIGN_K_CMD_RSP_BUFF ; 
 int PI_CMD_REQ_K_NUM_ENTRIES ; 
 int PI_CMD_REQ_K_SIZE_MAX ; 
 int PI_CMD_RSP_K_NUM_ENTRIES ; 
 int PI_CMD_RSP_K_SIZE_MAX ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_CMD_REQ_PROD ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_CMD_RSP_PROD ; 
 int PI_RCV_DESCR_M_SOP ; 
 int PI_RCV_DESCR_V_SEG_LEN ; 
 int PI_STATE_K_DMA_UNAVAIL ; 
 int PI_STATE_K_HALTED ; 
 int PI_STATE_K_RESET ; 
 int PI_STATE_K_UPGRADE ; 
 int PI_XMT_DESCR_M_EOP ; 
 int PI_XMT_DESCR_M_SOP ; 
 int PI_XMT_DESCR_V_SEG_LEN ; 
 int dfx_hw_adap_state_rd (TYPE_9__*) ; 
 int /*<<< orphan*/  dfx_port_write_long (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dfx_hw_dma_cmd_req(DFX_board_t *bp)
	{
	int status;			/* adapter status */
	int timeout_cnt;	/* used in for loops */

	/* Make sure the adapter is in a state that we can issue the DMA command in */

	status = dfx_hw_adap_state_rd(bp);
	if ((status == PI_STATE_K_RESET)		||
		(status == PI_STATE_K_HALTED)		||
		(status == PI_STATE_K_DMA_UNAVAIL)	||
		(status == PI_STATE_K_UPGRADE))
		return DFX_K_OUTSTATE;

	/* Put response buffer on the command response queue */

	bp->descr_block_virt->cmd_rsp[bp->cmd_rsp_reg.index.prod].long_0 = (u32) (PI_RCV_DESCR_M_SOP |
			((PI_CMD_RSP_K_SIZE_MAX / PI_ALIGN_K_CMD_RSP_BUFF) << PI_RCV_DESCR_V_SEG_LEN));
	bp->descr_block_virt->cmd_rsp[bp->cmd_rsp_reg.index.prod].long_1 = bp->cmd_rsp_phys;

	/* Bump (and wrap) the producer index and write out to register */

	bp->cmd_rsp_reg.index.prod += 1;
	bp->cmd_rsp_reg.index.prod &= PI_CMD_RSP_K_NUM_ENTRIES-1;
	dfx_port_write_long(bp, PI_PDQ_K_REG_CMD_RSP_PROD, bp->cmd_rsp_reg.lword);

	/* Put request buffer on the command request queue */

	bp->descr_block_virt->cmd_req[bp->cmd_req_reg.index.prod].long_0 = (u32) (PI_XMT_DESCR_M_SOP |
			PI_XMT_DESCR_M_EOP | (PI_CMD_REQ_K_SIZE_MAX << PI_XMT_DESCR_V_SEG_LEN));
	bp->descr_block_virt->cmd_req[bp->cmd_req_reg.index.prod].long_1 = bp->cmd_req_phys;

	/* Bump (and wrap) the producer index and write out to register */

	bp->cmd_req_reg.index.prod += 1;
	bp->cmd_req_reg.index.prod &= PI_CMD_REQ_K_NUM_ENTRIES-1;
	dfx_port_write_long(bp, PI_PDQ_K_REG_CMD_REQ_PROD, bp->cmd_req_reg.lword);

	/*
	 * Here we wait for the command request consumer index to be equal
	 * to the producer, indicating that the adapter has DMAed the request.
	 */

	for (timeout_cnt = 20000; timeout_cnt > 0; timeout_cnt--)
		{
		if (bp->cmd_req_reg.index.prod == (u8)(bp->cons_block_virt->cmd_req))
			break;
		udelay(100);			/* wait for 100 microseconds */
		}
	if (timeout_cnt == 0)
		return DFX_K_HW_TIMEOUT;

	/* Bump (and wrap) the completion index and write out to register */

	bp->cmd_req_reg.index.comp += 1;
	bp->cmd_req_reg.index.comp &= PI_CMD_REQ_K_NUM_ENTRIES-1;
	dfx_port_write_long(bp, PI_PDQ_K_REG_CMD_REQ_PROD, bp->cmd_req_reg.lword);

	/*
	 * Here we wait for the command response consumer index to be equal
	 * to the producer, indicating that the adapter has DMAed the response.
	 */

	for (timeout_cnt = 20000; timeout_cnt > 0; timeout_cnt--)
		{
		if (bp->cmd_rsp_reg.index.prod == (u8)(bp->cons_block_virt->cmd_rsp))
			break;
		udelay(100);			/* wait for 100 microseconds */
		}
	if (timeout_cnt == 0)
		return DFX_K_HW_TIMEOUT;

	/* Bump (and wrap) the completion index and write out to register */

	bp->cmd_rsp_reg.index.comp += 1;
	bp->cmd_rsp_reg.index.comp &= PI_CMD_RSP_K_NUM_ENTRIES-1;
	dfx_port_write_long(bp, PI_PDQ_K_REG_CMD_RSP_PROD, bp->cmd_rsp_reg.lword);
	return DFX_K_SUCCESS;
	}