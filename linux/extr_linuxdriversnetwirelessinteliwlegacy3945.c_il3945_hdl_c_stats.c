#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_RX (char*) ; 
 int UCODE_STATS_CLEAR_MSK ; 
 int /*<<< orphan*/  il3945_hdl_stats (struct il_priv*,struct il_rx_buf*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

void
il3945_hdl_c_stats(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	__le32 *flag = (__le32 *) &pkt->u.raw;

	if (le32_to_cpu(*flag) & UCODE_STATS_CLEAR_MSK) {
#ifdef CONFIG_IWLEGACY_DEBUGFS
		memset(&il->_3945.accum_stats, 0,
		       sizeof(struct il3945_notif_stats));
		memset(&il->_3945.delta_stats, 0,
		       sizeof(struct il3945_notif_stats));
		memset(&il->_3945.max_delta, 0,
		       sizeof(struct il3945_notif_stats));
#endif
		D_RX("Statistics have been cleared\n");
	}
	il3945_hdl_stats(il, rxb);
}