#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;
struct il_rx_pkt {TYPE_2__ u; TYPE_1__ hdr; int /*<<< orphan*/  len_n_flags; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_RADIO (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IL_DL_RADIO ; 
 int IL_RX_FRAME_SIZE_MSK ; 
 int /*<<< orphan*/  il_get_cmd_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_print_hex_dump (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

void
il_hdl_pm_debug_stats(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	u32 len = le32_to_cpu(pkt->len_n_flags) & IL_RX_FRAME_SIZE_MSK;
	D_RADIO("Dumping %d bytes of unhandled notification for %s:\n", len,
		il_get_cmd_string(pkt->hdr.cmd));
	il_print_hex_dump(il, IL_DL_RADIO, pkt->u.raw, len);
}