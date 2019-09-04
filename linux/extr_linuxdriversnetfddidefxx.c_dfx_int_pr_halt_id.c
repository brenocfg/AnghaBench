#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  int PI_UINT32 ;
typedef  TYPE_2__ DFX_board_t ;

/* Variables and functions */
#define  PI_HALT_ID_K_BUS_EXCEPTION 136 
#define  PI_HALT_ID_K_DMA_ERROR 135 
#define  PI_HALT_ID_K_HOST_DIR_HALT 134 
#define  PI_HALT_ID_K_HW_FAULT 133 
#define  PI_HALT_ID_K_IMAGE_CRC_ERROR 132 
#define  PI_HALT_ID_K_PARITY_ERROR 131 
#define  PI_HALT_ID_K_PC_TRACE 130 
#define  PI_HALT_ID_K_SELFTEST_TIMEOUT 129 
#define  PI_HALT_ID_K_SW_FAULT 128 
 int /*<<< orphan*/  PI_PDQ_K_REG_PORT_STATUS ; 
 int PI_PSTATUS_M_HALT_ID ; 
 int PI_PSTATUS_V_HALT_ID ; 
 int /*<<< orphan*/  dfx_port_read_long (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void dfx_int_pr_halt_id(DFX_board_t	*bp)
	{
	PI_UINT32	port_status;			/* PDQ port status register value */
	PI_UINT32	halt_id;				/* PDQ port status halt ID */

	/* Read the latest port status */

	dfx_port_read_long(bp, PI_PDQ_K_REG_PORT_STATUS, &port_status);

	/* Display halt state transition information */

	halt_id = (port_status & PI_PSTATUS_M_HALT_ID) >> PI_PSTATUS_V_HALT_ID;
	switch (halt_id)
		{
		case PI_HALT_ID_K_SELFTEST_TIMEOUT:
			printk("%s: Halt ID: Selftest Timeout\n", bp->dev->name);
			break;

		case PI_HALT_ID_K_PARITY_ERROR:
			printk("%s: Halt ID: Host Bus Parity Error\n", bp->dev->name);
			break;

		case PI_HALT_ID_K_HOST_DIR_HALT:
			printk("%s: Halt ID: Host-Directed Halt\n", bp->dev->name);
			break;

		case PI_HALT_ID_K_SW_FAULT:
			printk("%s: Halt ID: Adapter Software Fault\n", bp->dev->name);
			break;

		case PI_HALT_ID_K_HW_FAULT:
			printk("%s: Halt ID: Adapter Hardware Fault\n", bp->dev->name);
			break;

		case PI_HALT_ID_K_PC_TRACE:
			printk("%s: Halt ID: FDDI Network PC Trace Path Test\n", bp->dev->name);
			break;

		case PI_HALT_ID_K_DMA_ERROR:
			printk("%s: Halt ID: Adapter DMA Error\n", bp->dev->name);
			break;

		case PI_HALT_ID_K_IMAGE_CRC_ERROR:
			printk("%s: Halt ID: Firmware Image CRC Error\n", bp->dev->name);
			break;

		case PI_HALT_ID_K_BUS_EXCEPTION:
			printk("%s: Halt ID: 68000 Bus Exception\n", bp->dev->name);
			break;

		default:
			printk("%s: Halt ID: Unknown (code = %X)\n", bp->dev->name, halt_id);
			break;
		}
	}