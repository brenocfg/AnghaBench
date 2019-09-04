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
struct esas2r_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  disable_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_FIRST_INIT ; 
 int /*<<< orphan*/  AF_POWER_DOWN ; 
 int /*<<< orphan*/  AF_POWER_MGT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int esas2r_check_adapter (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_init_adapter_hw (struct esas2r_adapter*,int) ; 
 int /*<<< orphan*/  esas2r_init_pci_cfg_space (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_send_reset_ae (struct esas2r_adapter*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool esas2r_power_up(struct esas2r_adapter *a, bool init_poll)
{
	bool ret;

	clear_bit(AF_POWER_DOWN, &a->flags);
	esas2r_init_pci_cfg_space(a);
	set_bit(AF_FIRST_INIT, &a->flags);
	atomic_inc(&a->disable_cnt);

	/* reinitialize the adapter */
	ret = esas2r_check_adapter(a);
	if (!esas2r_init_adapter_hw(a, init_poll))
		ret = false;

	/* send the reset asynchronous event */
	esas2r_send_reset_ae(a, true);

	/* clear this flag after initialization. */
	clear_bit(AF_POWER_MGT, &a->flags);
	return ret;
}