#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  lword; } ;
struct TYPE_10__ {TYPE_1__ rcv_xmt_reg; } ;
typedef  int PI_UINT32 ;
typedef  TYPE_2__ DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  PI_PDQ_K_REG_PORT_STATUS ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_TYPE_2_PROD ; 
 int PI_PSTATUS_M_TYPE_0_PENDING ; 
 int /*<<< orphan*/  dfx_int_type_0_process (TYPE_2__*) ; 
 int /*<<< orphan*/  dfx_port_read_long (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dfx_port_write_long (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfx_rcv_queue_process (TYPE_2__*) ; 
 scalar_t__ dfx_xmt_done (TYPE_2__*) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void dfx_int_common(struct net_device *dev)
{
	DFX_board_t *bp = netdev_priv(dev);
	PI_UINT32	port_status;		/* Port Status register */

	/* Process xmt interrupts - frequent case, so always call this routine */

	if(dfx_xmt_done(bp))				/* free consumed xmt packets */
		netif_wake_queue(dev);

	/* Process rcv interrupts - frequent case, so always call this routine */

	dfx_rcv_queue_process(bp);		/* service received LLC frames */

	/*
	 * Transmit and receive producer and completion indices are updated on the
	 * adapter by writing to the Type 2 Producer register.  Since the frequent
	 * case is that we'll be processing either LLC transmit or receive buffers,
	 * we'll optimize I/O writes by doing a single register write here.
	 */

	dfx_port_write_long(bp, PI_PDQ_K_REG_TYPE_2_PROD, bp->rcv_xmt_reg.lword);

	/* Read PDQ Port Status register to find out which interrupts need processing */

	dfx_port_read_long(bp, PI_PDQ_K_REG_PORT_STATUS, &port_status);

	/* Process Type 0 interrupts (if any) - infrequent, so only call when needed */

	if (port_status & PI_PSTATUS_M_TYPE_0_PENDING)
		dfx_int_type_0_process(bp);	/* process Type 0 interrupts */
	}