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
typedef  int u32 ;
struct pqi_ctrl_info {int irq_mode; TYPE_1__* pqi_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  legacy_intx_status; } ;

/* Variables and functions */
#define  IRQ_MODE_INTX 130 
#define  IRQ_MODE_MSIX 129 
#define  IRQ_MODE_NONE 128 
 int PQI_LEGACY_INTX_PENDING ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool pqi_is_valid_irq(struct pqi_ctrl_info *ctrl_info)
{
	bool valid_irq;
	u32 intx_status;

	switch (ctrl_info->irq_mode) {
	case IRQ_MODE_MSIX:
		valid_irq = true;
		break;
	case IRQ_MODE_INTX:
		intx_status =
			readl(&ctrl_info->pqi_registers->legacy_intx_status);
		if (intx_status & PQI_LEGACY_INTX_PENDING)
			valid_irq = true;
		else
			valid_irq = false;
		break;
	case IRQ_MODE_NONE:
	default:
		valid_irq = false;
		break;
	}

	return valid_irq;
}