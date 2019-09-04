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
typedef  int u32 ;
typedef  int u16 ;
struct il_priv {int scd_base_addr; } ;

/* Variables and functions */
 int IL49_SCD_TRANSLATE_TBL_OFFSET_QUEUE (int) ; 
 int IL_SCD_QUEUE_RA_TID_MAP_RATID_MSK ; 
 int il_read_targ_mem (struct il_priv*,int) ; 
 int /*<<< orphan*/  il_write_targ_mem (struct il_priv*,int,int) ; 

__attribute__((used)) static int
il4965_tx_queue_set_q2ratid(struct il_priv *il, u16 ra_tid, u16 txq_id)
{
	u32 tbl_dw_addr;
	u32 tbl_dw;
	u16 scd_q2ratid;

	scd_q2ratid = ra_tid & IL_SCD_QUEUE_RA_TID_MAP_RATID_MSK;

	tbl_dw_addr =
	    il->scd_base_addr + IL49_SCD_TRANSLATE_TBL_OFFSET_QUEUE(txq_id);

	tbl_dw = il_read_targ_mem(il, tbl_dw_addr);

	if (txq_id & 0x1)
		tbl_dw = (scd_q2ratid << 16) | (tbl_dw & 0x0000FFFF);
	else
		tbl_dw = scd_q2ratid | (tbl_dw & 0xFFFF0000);

	il_write_targ_mem(il, tbl_dw_addr, tbl_dw);

	return 0;
}