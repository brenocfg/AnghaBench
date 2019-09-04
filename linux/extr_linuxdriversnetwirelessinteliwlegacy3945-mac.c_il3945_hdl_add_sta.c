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
struct il_rx_buf {int dummy; } ;
struct il_priv {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_RX (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* pkt ; 

__attribute__((used)) static void
il3945_hdl_add_sta(struct il_priv *il, struct il_rx_buf *rxb)
{
#ifdef CONFIG_IWLEGACY_DEBUG
	struct il_rx_pkt *pkt = rxb_addr(rxb);
#endif

	D_RX("Received C_ADD_STA: 0x%02X\n", pkt->u.status);
}