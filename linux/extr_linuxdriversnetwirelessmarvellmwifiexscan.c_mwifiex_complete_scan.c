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
struct mwifiex_private {int /*<<< orphan*/  scan_request; struct mwifiex_adapter* adapter; } ;
struct TYPE_3__ {scalar_t__ status; } ;
struct mwifiex_adapter {TYPE_2__* curr_cmd; TYPE_1__ cmd_wait_q; scalar_t__ survey_idx; } ;
struct TYPE_4__ {scalar_t__ wait_q_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  mwifiex_complete_cmd (struct mwifiex_adapter*,TYPE_2__*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mwifiex_complete_scan(struct mwifiex_private *priv)
{
	struct mwifiex_adapter *adapter = priv->adapter;

	adapter->survey_idx = 0;
	if (adapter->curr_cmd->wait_q_enabled) {
		adapter->cmd_wait_q.status = 0;
		if (!priv->scan_request) {
			mwifiex_dbg(adapter, INFO,
				    "complete internal scan\n");
			mwifiex_complete_cmd(adapter, adapter->curr_cmd);
		}
	}
}