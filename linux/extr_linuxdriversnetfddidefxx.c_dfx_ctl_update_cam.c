#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * entry; } ;
struct TYPE_8__ {TYPE_1__ addr_filter_set; int /*<<< orphan*/  cmd_type; } ;
struct TYPE_7__ {int uc_count; int /*<<< orphan*/ * mc_table; scalar_t__ mc_count; int /*<<< orphan*/ * uc_table; TYPE_3__* cmd_req_virt; } ;
typedef  int /*<<< orphan*/  PI_LAN_ADDR ;
typedef  TYPE_2__ DFX_board_t ;

/* Variables and functions */
 int DFX_K_FAILURE ; 
 scalar_t__ DFX_K_SUCCESS ; 
 int FDDI_K_ALEN ; 
 int PI_CMD_ADDR_FILTER_K_SIZE ; 
 int /*<<< orphan*/  PI_CMD_K_ADDR_FILTER_SET ; 
 int /*<<< orphan*/  PI_CMD_REQ_K_SIZE_MAX ; 
 scalar_t__ dfx_hw_dma_cmd_req (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dfx_ctl_update_cam(DFX_board_t *bp)
	{
	int			i;				/* used as index */
	PI_LAN_ADDR	*p_addr;		/* pointer to CAM entry */

	/*
	 * Fill in command request information
	 *
	 * Note: Even though both the unicast and multicast address
	 *       table entries are stored as contiguous 6 byte entries,
	 *		 the firmware address filter set command expects each
	 *		 entry to be two longwords (8 bytes total).  We must be
	 *		 careful to only copy the six bytes of each unicast and
	 *		 multicast table entry into each command entry.  This
	 *		 is also why we must first clear the entire command
	 *		 request buffer.
	 */

	memset(bp->cmd_req_virt, 0, PI_CMD_REQ_K_SIZE_MAX);	/* first clear buffer */
	bp->cmd_req_virt->cmd_type = PI_CMD_K_ADDR_FILTER_SET;
	p_addr = &bp->cmd_req_virt->addr_filter_set.entry[0];

	/* Now add unicast addresses to command request buffer, if any */

	for (i=0; i < (int)bp->uc_count; i++)
		{
		if (i < PI_CMD_ADDR_FILTER_K_SIZE)
			{
			memcpy(p_addr, &bp->uc_table[i*FDDI_K_ALEN], FDDI_K_ALEN);
			p_addr++;			/* point to next command entry */
			}
		}

	/* Now add multicast addresses to command request buffer, if any */

	for (i=0; i < (int)bp->mc_count; i++)
		{
		if ((i + bp->uc_count) < PI_CMD_ADDR_FILTER_K_SIZE)
			{
			memcpy(p_addr, &bp->mc_table[i*FDDI_K_ALEN], FDDI_K_ALEN);
			p_addr++;			/* point to next command entry */
			}
		}

	/* Issue command to update adapter CAM, then return */

	if (dfx_hw_dma_cmd_req(bp) != DFX_K_SUCCESS)
		return DFX_K_FAILURE;
	return DFX_K_SUCCESS;
	}