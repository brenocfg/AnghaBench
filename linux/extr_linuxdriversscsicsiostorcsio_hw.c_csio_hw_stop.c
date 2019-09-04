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
struct csio_hw {int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_HWE_PCI_REMOVE ; 
 int EINVAL ; 
 scalar_t__ csio_is_hw_removing (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
csio_hw_stop(struct csio_hw *hw)
{
	csio_post_event(&hw->sm, CSIO_HWE_PCI_REMOVE);

	if (csio_is_hw_removing(hw))
		return 0;
	else
		return -EINVAL;
}