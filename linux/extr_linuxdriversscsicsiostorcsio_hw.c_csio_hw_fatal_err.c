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
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBALENABLE_F ; 
 int /*<<< orphan*/  SGE_CONTROL_A ; 
 int /*<<< orphan*/  csio_fatal (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_hw_intr_disable (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_set_reg_field (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
csio_hw_fatal_err(struct csio_hw *hw)
{
	csio_set_reg_field(hw, SGE_CONTROL_A, GLOBALENABLE_F, 0);
	csio_hw_intr_disable(hw);

	/* Do not reset HW, we may need FW state for debugging */
	csio_fatal(hw, "HW Fatal error encountered!\n");
}