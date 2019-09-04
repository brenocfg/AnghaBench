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
struct iwl_trans {TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {int max_tfd_queue_size; } ;

/* Variables and functions */

__attribute__((used)) static inline int iwl_queue_dec_wrap(struct iwl_trans *trans, int index)
{
	return --index & (trans->cfg->base_params->max_tfd_queue_size - 1);
}