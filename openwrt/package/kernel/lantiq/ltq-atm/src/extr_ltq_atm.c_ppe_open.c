#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct port {scalar_t__ tx_max_cell_rate; scalar_t__ tx_current_cell_rate; } ;
struct TYPE_8__ {int traffic_class; scalar_t__ max_pcr; scalar_t__ scr; scalar_t__ min_pcr; } ;
struct TYPE_10__ {scalar_t__ aal; TYPE_2__ txtp; } ;
struct atm_vcc {short vpi; int vci; int itf; TYPE_4__ qos; TYPE_3__* dev; int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {int sbid; } ;
struct TYPE_11__ {scalar_t__ conn_table; TYPE_1__* conn; struct port* port; } ;
struct TYPE_9__ {scalar_t__ dev_data; } ;
struct TYPE_7__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 scalar_t__ ATM_AAL0 ; 
 scalar_t__ ATM_AAL5 ; 
#define  ATM_CBR 131 
#define  ATM_UBR_PLUS 130 
#define  ATM_VBR_NRT 129 
#define  ATM_VBR_RT 128 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int FIRST_QSB_QID ; 
 int MAX_PVC_NUMBER ; 
 int* MBOX_IGU1_IER ; 
 int* MBOX_IGU1_ISRC ; 
 int /*<<< orphan*/  PPE_MAILBOX_IGU1_INT ; 
 int RX_DMA_CH_AAL ; 
 int RX_DMA_CH_OAM ; 
 TYPE_6__* WTX_QUEUE_CONFIG (int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int find_vpivci (short,int) ; 
 TYPE_5__ g_atm_priv_data ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_htu_entry (short,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_qsb (struct atm_vcc*,TYPE_4__*,int) ; 
 scalar_t__ test_and_set_bit (int,scalar_t__*) ; 

__attribute__((used)) static int ppe_open(struct atm_vcc *vcc)
{
	int ret;
	short vpi = vcc->vpi;
	int   vci = vcc->vci;
	struct port *port = &g_atm_priv_data.port[(int)vcc->dev->dev_data];
	int conn;
	int f_enable_irq = 0;

	if ( vcc->qos.aal != ATM_AAL5 && vcc->qos.aal != ATM_AAL0 )
		return -EPROTONOSUPPORT;

#if !defined(DISABLE_QOS_WORKAROUND) || !DISABLE_QOS_WORKAROUND
	/*  check bandwidth */
	if ( (vcc->qos.txtp.traffic_class == ATM_CBR && vcc->qos.txtp.max_pcr > (port->tx_max_cell_rate - port->tx_current_cell_rate))
		|| (vcc->qos.txtp.traffic_class == ATM_VBR_RT && vcc->qos.txtp.max_pcr > (port->tx_max_cell_rate - port->tx_current_cell_rate))
#if 0
		|| (vcc->qos.txtp.traffic_class == ATM_VBR_NRT && vcc->qos.txtp.scr > (port->tx_max_cell_rate - port->tx_current_cell_rate))
#endif
		|| (vcc->qos.txtp.traffic_class == ATM_UBR_PLUS && vcc->qos.txtp.min_pcr > (port->tx_max_cell_rate - port->tx_current_cell_rate)) )
	{
		ret = -EINVAL;
		goto PPE_OPEN_EXIT;
	}
#endif

	/*  check existing vpi,vci  */
	conn = find_vpivci(vpi, vci);
	if ( conn >= 0 ) {
		ret = -EADDRINUSE;
		goto PPE_OPEN_EXIT;
	}

	/*  check whether it need to enable irq */
	if ( g_atm_priv_data.conn_table == 0 )
		f_enable_irq = 1;

	/*  allocate connection */
	for ( conn = 0; conn < MAX_PVC_NUMBER; conn++ ) {
		if ( test_and_set_bit(conn, &g_atm_priv_data.conn_table) == 0 ) {
			g_atm_priv_data.conn[conn].vcc = vcc;
			break;
		}
	}
	if ( conn == MAX_PVC_NUMBER ) {
		ret = -EINVAL;
		goto PPE_OPEN_EXIT;
	}

	/*  reserve bandwidth   */
	switch ( vcc->qos.txtp.traffic_class ) {
	case ATM_CBR:
	case ATM_VBR_RT:
		port->tx_current_cell_rate += vcc->qos.txtp.max_pcr;
		break;
	case ATM_VBR_NRT:
#if 0
		port->tx_current_cell_rate += vcc->qos.txtp.scr;
#endif
		break;
	case ATM_UBR_PLUS:
		port->tx_current_cell_rate += vcc->qos.txtp.min_pcr;
		break;
	}

	/*  set qsb */
	set_qsb(vcc, &vcc->qos, conn);

	/*  update atm_vcc structure    */
	vcc->itf = (int)vcc->dev->dev_data;
	vcc->vpi = vpi;
	vcc->vci = vci;
	set_bit(ATM_VF_READY, &vcc->flags);

	/*  enable irq  */
	if ( f_enable_irq ) {
		*MBOX_IGU1_ISRC = (1 << RX_DMA_CH_AAL) | (1 << RX_DMA_CH_OAM);
		*MBOX_IGU1_IER  = (1 << RX_DMA_CH_AAL) | (1 << RX_DMA_CH_OAM);

		enable_irq(PPE_MAILBOX_IGU1_INT);
	}

	/*  set port    */
	WTX_QUEUE_CONFIG(conn + FIRST_QSB_QID)->sbid = (int)vcc->dev->dev_data;

	/*  set htu entry   */
	set_htu_entry(vpi, vci, conn, vcc->qos.aal == ATM_AAL5 ? 1 : 0, 0);

	*MBOX_IGU1_ISRC |= (1 << (conn + FIRST_QSB_QID + 16));
	*MBOX_IGU1_IER |= (1 << (conn + FIRST_QSB_QID + 16));

	ret = 0;

PPE_OPEN_EXIT:
	return ret;
}