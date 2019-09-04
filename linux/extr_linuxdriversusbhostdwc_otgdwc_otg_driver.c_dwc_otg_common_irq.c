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
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (scalar_t__) ; 
 int /*<<< orphan*/  S3C2410X_CLEAR_EINTPEND () ; 
 scalar_t__ dwc_otg_handle_common_intr (void*) ; 

__attribute__((used)) static irqreturn_t dwc_otg_common_irq(int irq, void *dev)
{
	int32_t retval = IRQ_NONE;

	retval = dwc_otg_handle_common_intr(dev);
	if (retval != 0) {
		S3C2410X_CLEAR_EINTPEND();
	}
	return IRQ_RETVAL(retval);
}