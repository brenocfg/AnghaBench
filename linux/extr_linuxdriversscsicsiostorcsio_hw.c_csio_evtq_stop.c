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
struct csio_hw {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_HWF_FWEVT_STOP ; 

__attribute__((used)) static void
csio_evtq_stop(struct csio_hw *hw)
{
	hw->flags |= CSIO_HWF_FWEVT_STOP;
}