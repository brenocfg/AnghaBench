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
struct spi_controller {int /*<<< orphan*/  transfer_one_message; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  transfer; TYPE_1__* mem_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  exec_op; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int spi_controller_check_ops(struct spi_controller *ctlr)
{
	/*
	 * The controller may implement only the high-level SPI-memory like
	 * operations if it does not support regular SPI transfers, and this is
	 * valid use case.
	 * If ->mem_ops is NULL, we request that at least one of the
	 * ->transfer_xxx() method be implemented.
	 */
	if (ctlr->mem_ops) {
		if (!ctlr->mem_ops->exec_op)
			return -EINVAL;
	} else if (!ctlr->transfer && !ctlr->transfer_one &&
		   !ctlr->transfer_one_message) {
		return -EINVAL;
	}

	return 0;
}