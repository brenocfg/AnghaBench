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
struct pvscsi_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int PVSCSI_INTR_ALL_SUPPORTED ; 
 int /*<<< orphan*/  pvscsi_isr (int,void*) ; 
 int pvscsi_read_intr_status (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_write_intr_status (void*,int) ; 

__attribute__((used)) static irqreturn_t pvscsi_shared_isr(int irq, void *devp)
{
	struct pvscsi_adapter *adapter = devp;
	u32 val = pvscsi_read_intr_status(adapter);

	if (!(val & PVSCSI_INTR_ALL_SUPPORTED))
		return IRQ_NONE;
	pvscsi_write_intr_status(devp, val);
	return pvscsi_isr(irq, devp);
}