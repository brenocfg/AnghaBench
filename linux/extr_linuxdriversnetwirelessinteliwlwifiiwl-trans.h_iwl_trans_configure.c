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
struct iwl_trans_config {int /*<<< orphan*/  op_mode; } ;
struct iwl_trans {TYPE_1__* ops; int /*<<< orphan*/  op_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* configure ) (struct iwl_trans*,struct iwl_trans_config const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_cmd_groups_verify_sorted (struct iwl_trans_config const*) ; 
 int /*<<< orphan*/  stub1 (struct iwl_trans*,struct iwl_trans_config const*) ; 

__attribute__((used)) static inline void iwl_trans_configure(struct iwl_trans *trans,
				       const struct iwl_trans_config *trans_cfg)
{
	trans->op_mode = trans_cfg->op_mode;

	trans->ops->configure(trans, trans_cfg);
	WARN_ON(iwl_cmd_groups_verify_sorted(trans_cfg));
}