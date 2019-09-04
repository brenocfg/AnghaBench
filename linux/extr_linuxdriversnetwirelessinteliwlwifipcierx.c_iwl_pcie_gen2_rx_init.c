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
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int _iwl_pcie_rx_init (struct iwl_trans*) ; 

int iwl_pcie_gen2_rx_init(struct iwl_trans *trans)
{
	/*
	 * We don't configure the RFH.
	 * Restock will be done at alive, after firmware configured the RFH.
	 */
	return _iwl_pcie_rx_init(trans);
}