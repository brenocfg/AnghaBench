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
typedef  int PI_UINT32 ;
typedef  int /*<<< orphan*/  DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  PI_PDQ_K_REG_PORT_STATUS ; 
 int PI_PSTATUS_M_STATE ; 
 int PI_PSTATUS_V_STATE ; 
 int /*<<< orphan*/  dfx_port_read_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int dfx_hw_adap_state_rd(DFX_board_t *bp)
	{
	PI_UINT32 port_status;		/* Port Status register value */

	dfx_port_read_long(bp, PI_PDQ_K_REG_PORT_STATUS, &port_status);
	return (port_status & PI_PSTATUS_M_STATE) >> PI_PSTATUS_V_STATE;
	}