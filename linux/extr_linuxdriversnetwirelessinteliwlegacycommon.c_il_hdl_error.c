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
struct TYPE_4__ {int /*<<< orphan*/  error_info; int /*<<< orphan*/  bad_cmd_seq_num; int /*<<< orphan*/  cmd_id; int /*<<< orphan*/  error_type; } ;
struct TYPE_3__ {TYPE_2__ err_resp; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_get_cmd_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

void
il_hdl_error(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);

	IL_ERR("Error Reply type 0x%08X cmd %s (0x%02X) "
	       "seq 0x%04X ser 0x%08X\n",
	       le32_to_cpu(pkt->u.err_resp.error_type),
	       il_get_cmd_string(pkt->u.err_resp.cmd_id),
	       pkt->u.err_resp.cmd_id,
	       le16_to_cpu(pkt->u.err_resp.bad_cmd_seq_num),
	       le32_to_cpu(pkt->u.err_resp.error_info));
}