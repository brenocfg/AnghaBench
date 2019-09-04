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

/* Variables and functions */
#define  FH_TSSR_TX_ERROR_REG 132 
#define  FH_TSSR_TX_STATUS_REG 131 
 int IWL_MAX_RX_HW_QUEUES ; 
#define  RFH_GEN_CFG 130 
#define  RFH_GEN_STATUS 129 
 int RFH_Q_FRBDCB_BA_LSB (int) ; 
 int RFH_Q_FRBDCB_RIDX (int) ; 
 int RFH_Q_FRBDCB_WIDX (int) ; 
 int RFH_Q_URBD_STTS_WPTR_LSB (int) ; 
#define  RFH_RXF_DMA_CFG 128 

__attribute__((used)) static const char *get_rfh_string(int cmd)
{
#define IWL_CMD(x) case x: return #x
#define IWL_CMD_MQ(arg, reg, q) { if (arg == reg(q)) return #reg; }

	int i;

	for (i = 0; i < IWL_MAX_RX_HW_QUEUES; i++) {
		IWL_CMD_MQ(cmd, RFH_Q_FRBDCB_BA_LSB, i);
		IWL_CMD_MQ(cmd, RFH_Q_FRBDCB_WIDX, i);
		IWL_CMD_MQ(cmd, RFH_Q_FRBDCB_RIDX, i);
		IWL_CMD_MQ(cmd, RFH_Q_URBD_STTS_WPTR_LSB, i);
	}

	switch (cmd) {
	IWL_CMD(RFH_RXF_DMA_CFG);
	IWL_CMD(RFH_GEN_CFG);
	IWL_CMD(RFH_GEN_STATUS);
	IWL_CMD(FH_TSSR_TX_STATUS_REG);
	IWL_CMD(FH_TSSR_TX_ERROR_REG);
	default:
		return "UNKNOWN";
	}
#undef IWL_CMD_MQ
}