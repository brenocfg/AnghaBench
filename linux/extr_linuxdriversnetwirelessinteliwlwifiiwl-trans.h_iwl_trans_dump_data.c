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
struct iwl_trans_dump_data {int dummy; } ;
struct iwl_trans {TYPE_1__* ops; } ;
struct iwl_fw_dbg_trigger_tlv {int dummy; } ;
struct TYPE_2__ {struct iwl_trans_dump_data* (* dump_data ) (struct iwl_trans*,struct iwl_fw_dbg_trigger_tlv const*) ;} ;

/* Variables and functions */
 struct iwl_trans_dump_data* stub1 (struct iwl_trans*,struct iwl_fw_dbg_trigger_tlv const*) ; 

__attribute__((used)) static inline struct iwl_trans_dump_data *
iwl_trans_dump_data(struct iwl_trans *trans,
		    const struct iwl_fw_dbg_trigger_tlv *trigger)
{
	if (!trans->ops->dump_data)
		return NULL;
	return trans->ops->dump_data(trans, trigger);
}