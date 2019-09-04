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
typedef  int u8 ;
struct tx_desc {int /*<<< orphan*/  txdw7; int /*<<< orphan*/  txdw6; int /*<<< orphan*/  txdw5; int /*<<< orphan*/  txdw4; int /*<<< orphan*/  txdw3; int /*<<< orphan*/  txdw2; int /*<<< orphan*/  txdw1; int /*<<< orphan*/  txdw0; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int DATA_FRAMETAG ; 
 int /*<<< orphan*/  DBG_88E (char*,...) ; 
 int /*<<< orphan*/  HAL_DEF_DBG_DUMP_TXPKT ; 
 int MGNT_FRAMETAG ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (struct adapter*,int /*<<< orphan*/ ,int*) ; 

void _dbg_dump_tx_info(struct adapter *padapter, int frame_tag,
		       struct tx_desc *ptxdesc)
{
	u8 dmp_txpkt;
	bool dump_txdesc = false;

	rtw_hal_get_def_var(padapter, HAL_DEF_DBG_DUMP_TXPKT, &(dmp_txpkt));

	if (dmp_txpkt == 1) {/* dump txdesc for data frame */
		DBG_88E("dump tx_desc for data frame\n");
		if ((frame_tag & 0x0f) == DATA_FRAMETAG)
			dump_txdesc = true;
	} else if (dmp_txpkt == 2) {/* dump txdesc for mgnt frame */
		DBG_88E("dump tx_desc for mgnt frame\n");
		if ((frame_tag & 0x0f) == MGNT_FRAMETAG)
			dump_txdesc = true;
	}

	if (dump_txdesc) {
		DBG_88E("=====================================\n");
		DBG_88E("txdw0(0x%08x)\n", ptxdesc->txdw0);
		DBG_88E("txdw1(0x%08x)\n", ptxdesc->txdw1);
		DBG_88E("txdw2(0x%08x)\n", ptxdesc->txdw2);
		DBG_88E("txdw3(0x%08x)\n", ptxdesc->txdw3);
		DBG_88E("txdw4(0x%08x)\n", ptxdesc->txdw4);
		DBG_88E("txdw5(0x%08x)\n", ptxdesc->txdw5);
		DBG_88E("txdw6(0x%08x)\n", ptxdesc->txdw6);
		DBG_88E("txdw7(0x%08x)\n", ptxdesc->txdw7);
		DBG_88E("=====================================\n");
	}
}