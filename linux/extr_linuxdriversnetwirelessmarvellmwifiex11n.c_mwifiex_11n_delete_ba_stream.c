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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_private {int dummy; } ;
struct host_cmd_ds_11n_delba {int /*<<< orphan*/  peer_mac_addr; int /*<<< orphan*/  del_ba_param_set; } ;

/* Variables and functions */
 int DELBA_TID_POS ; 
 int /*<<< orphan*/  INITIATOR_BIT (int) ; 
 int /*<<< orphan*/  TYPE_DELBA_RECEIVE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_del_ba_tbl (struct mwifiex_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mwifiex_11n_delete_ba_stream(struct mwifiex_private *priv, u8 *del_ba)
{
	struct host_cmd_ds_11n_delba *cmd_del_ba =
		(struct host_cmd_ds_11n_delba *) del_ba;
	uint16_t del_ba_param_set = le16_to_cpu(cmd_del_ba->del_ba_param_set);
	int tid;

	tid = del_ba_param_set >> DELBA_TID_POS;

	mwifiex_del_ba_tbl(priv, tid, cmd_del_ba->peer_mac_addr,
			   TYPE_DELBA_RECEIVE, INITIATOR_BIT(del_ba_param_set));
}