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
typedef  int u16 ;

/* Variables and functions */
#define  BEACON_QUEUE 136 
#define  BE_QUEUE 135 
#define  BK_QUEUE 134 
#define  HCCA_QUEUE 133 
#define  HIGH_QUEUE 132 
#define  MGNT_QUEUE 131 
 int REG_BEQ_TXBD_IDX ; 
 int REG_BKQ_TXBD_IDX ; 
 int REG_HI0Q_TXBD_IDX ; 
 int REG_MGQ_TXBD_IDX ; 
 int REG_VIQ_TXBD_IDX ; 
 int REG_VOQ_TXBD_IDX ; 
#define  TXCMD_QUEUE 130 
#define  VI_QUEUE 129 
#define  VO_QUEUE 128 

__attribute__((used)) static u16 get_desc_addr_fr_q_idx(u16 queue_index)
{
	u16 desc_address = REG_BEQ_TXBD_IDX;

	switch (queue_index) {
	case BK_QUEUE:
		desc_address = REG_BKQ_TXBD_IDX;
		break;
	case BE_QUEUE:
		desc_address = REG_BEQ_TXBD_IDX;
		break;
	case VI_QUEUE:
		desc_address = REG_VIQ_TXBD_IDX;
		break;
	case VO_QUEUE:
		desc_address = REG_VOQ_TXBD_IDX;
		break;
	case BEACON_QUEUE:
		desc_address = REG_BEQ_TXBD_IDX;
		break;
	case TXCMD_QUEUE:
		desc_address = REG_BEQ_TXBD_IDX;
		break;
	case MGNT_QUEUE:
		desc_address = REG_MGQ_TXBD_IDX;
		break;
	case HIGH_QUEUE:
		desc_address = REG_HI0Q_TXBD_IDX;
		break;
	case HCCA_QUEUE:
		desc_address = REG_BEQ_TXBD_IDX;
		break;
	default:
		break;
	}
	return desc_address;
}