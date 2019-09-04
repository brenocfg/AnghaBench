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
struct iwl_priv {int dummy; } ;
struct iwl_op_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_OP_MODE_GET_DVM (struct iwl_op_mode*) ; 
 int /*<<< orphan*/  iwl_check_for_ct_kill (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_fw_error (struct iwl_priv*,int) ; 

__attribute__((used)) static void iwl_cmd_queue_full(struct iwl_op_mode *op_mode)
{
	struct iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	if (!iwl_check_for_ct_kill(priv)) {
		IWL_ERR(priv, "Restarting adapter queue is full\n");
		iwlagn_fw_error(priv, false);
	}
}