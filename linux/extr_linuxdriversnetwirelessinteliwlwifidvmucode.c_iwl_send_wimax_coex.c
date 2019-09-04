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
struct iwl_wimax_coex_cmd {int dummy; } ;
struct iwl_priv {int dummy; } ;
typedef  int /*<<< orphan*/  coex_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_PRIORITY_TABLE_CMD ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_wimax_coex_cmd*) ; 
 int /*<<< orphan*/  memset (struct iwl_wimax_coex_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_send_wimax_coex(struct iwl_priv *priv)
{
	struct iwl_wimax_coex_cmd coex_cmd;

	/* coexistence is disabled */
	memset(&coex_cmd, 0, sizeof(coex_cmd));

	return iwl_dvm_send_cmd_pdu(priv,
				COEX_PRIORITY_TABLE_CMD, 0,
				sizeof(coex_cmd), &coex_cmd);
}