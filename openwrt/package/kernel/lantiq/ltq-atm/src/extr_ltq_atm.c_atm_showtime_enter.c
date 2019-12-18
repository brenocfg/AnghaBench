#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct port_cell_info {int port_num; scalar_t__* tx_link_rate; } ;
struct TYPE_8__ {TYPE_2__* port; TYPE_1__* conn; } ;
struct TYPE_7__ {int /*<<< orphan*/  qos; } ;
struct TYPE_6__ {scalar_t__ tx_max_cell_rate; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_3__* vcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ATM_PHY_SIG_FOUND ; 
 int ATM_PORT_NUMBER ; 
 int /*<<< orphan*/  IFX_REG_W32 (int,int /*<<< orphan*/ ) ; 
 int MAX_PVC_NUMBER ; 
 int /*<<< orphan*/  UTP_CFG ; 
 int /*<<< orphan*/  atm_dev_signal_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ g_atm_priv_data ; 
 int g_showtime ; 
 void* g_xdata_addr ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  qsb_global_set () ; 
 int /*<<< orphan*/  set_qsb (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int atm_showtime_enter(struct port_cell_info *port_cell, void *xdata_addr)
{
	int i, j, port_num;

	ASSERT(port_cell != NULL, "port_cell is NULL");
	ASSERT(xdata_addr != NULL, "xdata_addr is NULL");

	for ( j = 0; j < ATM_PORT_NUMBER && j < port_cell->port_num; j++ )
		if ( port_cell->tx_link_rate[j] > 0 )
			break;
	for ( i = 0; i < ATM_PORT_NUMBER && i < port_cell->port_num; i++ )
		g_atm_priv_data.port[i].tx_max_cell_rate =
			port_cell->tx_link_rate[i] > 0 ? port_cell->tx_link_rate[i] : port_cell->tx_link_rate[j];

	qsb_global_set();

	for ( i = 0; i < MAX_PVC_NUMBER; i++ )
		if ( g_atm_priv_data.conn[i].vcc != NULL )
			set_qsb(g_atm_priv_data.conn[i].vcc, &g_atm_priv_data.conn[i].vcc->qos, i);

	//  TODO: ReTX set xdata_addr
	g_xdata_addr = xdata_addr;

	g_showtime = 1;

	for ( port_num = 0; port_num < ATM_PORT_NUMBER; port_num++ )
		atm_dev_signal_change(g_atm_priv_data.port[port_num].dev, ATM_PHY_SIG_FOUND);

#if defined(CONFIG_VR9)
	IFX_REG_W32(0x0F, UTP_CFG);
#endif

	printk("enter showtime, cell rate: 0 - %d, 1 - %d, xdata addr: 0x%08x\n",
		g_atm_priv_data.port[0].tx_max_cell_rate,
		g_atm_priv_data.port[1].tx_max_cell_rate,
		(unsigned int)g_xdata_addr);

	return 0;
}