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
struct pqi_ctrl_info {int irq_mode; } ;
typedef  enum pqi_irq_mode { ____Placeholder_pqi_irq_mode } pqi_irq_mode ;

/* Variables and functions */
#define  IRQ_MODE_INTX 130 
#define  IRQ_MODE_MSIX 129 
#define  IRQ_MODE_NONE 128 
 int /*<<< orphan*/  pqi_configure_legacy_intx (struct pqi_ctrl_info*,int) ; 
 int /*<<< orphan*/  sis_enable_intx (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  sis_enable_msix (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_change_irq_mode(struct pqi_ctrl_info *ctrl_info,
	enum pqi_irq_mode new_mode)
{
	switch (ctrl_info->irq_mode) {
	case IRQ_MODE_MSIX:
		switch (new_mode) {
		case IRQ_MODE_MSIX:
			break;
		case IRQ_MODE_INTX:
			pqi_configure_legacy_intx(ctrl_info, true);
			sis_enable_intx(ctrl_info);
			break;
		case IRQ_MODE_NONE:
			break;
		}
		break;
	case IRQ_MODE_INTX:
		switch (new_mode) {
		case IRQ_MODE_MSIX:
			pqi_configure_legacy_intx(ctrl_info, false);
			sis_enable_msix(ctrl_info);
			break;
		case IRQ_MODE_INTX:
			break;
		case IRQ_MODE_NONE:
			pqi_configure_legacy_intx(ctrl_info, false);
			break;
		}
		break;
	case IRQ_MODE_NONE:
		switch (new_mode) {
		case IRQ_MODE_MSIX:
			sis_enable_msix(ctrl_info);
			break;
		case IRQ_MODE_INTX:
			pqi_configure_legacy_intx(ctrl_info, true);
			sis_enable_intx(ctrl_info);
			break;
		case IRQ_MODE_NONE:
			break;
		}
		break;
	}

	ctrl_info->irq_mode = new_mode;
}