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
struct iwl_trans {TYPE_1__* cfg; } ;
struct iwl_rx_transfer_desc {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {scalar_t__ mq_rx_supported; } ;

/* Variables and functions */

__attribute__((used)) static int iwl_pcie_free_bd_size(struct iwl_trans *trans, bool use_rx_td)
{
	struct iwl_rx_transfer_desc *rx_td;

	if (use_rx_td)
		return sizeof(*rx_td);
	else
		return trans->cfg->mq_rx_supported ? sizeof(__le64) :
			sizeof(__le32);
}