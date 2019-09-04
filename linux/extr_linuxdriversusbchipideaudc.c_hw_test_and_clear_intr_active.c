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
typedef  int u32 ;
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_USBSTS ; 
 int hw_read_intr_enable (struct ci_hdrc*) ; 
 int hw_read_intr_status (struct ci_hdrc*) ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 hw_test_and_clear_intr_active(struct ci_hdrc *ci)
{
	u32 reg = hw_read_intr_status(ci) & hw_read_intr_enable(ci);

	hw_write(ci, OP_USBSTS, ~0, reg);
	return reg;
}