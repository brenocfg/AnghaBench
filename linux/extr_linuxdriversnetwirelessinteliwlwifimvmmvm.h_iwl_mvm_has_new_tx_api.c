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
struct iwl_mvm {TYPE_2__* trans; } ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {int use_tfh; } ;

/* Variables and functions */

__attribute__((used)) static inline bool iwl_mvm_has_new_tx_api(struct iwl_mvm *mvm)
{
	/* TODO - replace with TLV once defined */
	return mvm->trans->cfg->use_tfh;
}