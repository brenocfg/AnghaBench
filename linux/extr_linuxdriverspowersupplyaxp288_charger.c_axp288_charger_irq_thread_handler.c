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
struct axp288_chrg_info {int* irq; int /*<<< orphan*/  psy_usb; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  BAT_SAFE_ENTER_IRQ 136 
#define  BAT_SAFE_QUIT_IRQ 135 
#define  CBTO_IRQ 134 
#define  CBTU_IRQ 133 
#define  CHARGE_CHARGING_IRQ 132 
#define  CHARGE_DONE_IRQ 131 
 int CHRG_INTR_END ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
#define  QCBTO_IRQ 130 
#define  QCBTU_IRQ 129 
#define  VBUS_OV_IRQ 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t axp288_charger_irq_thread_handler(int irq, void *dev)
{
	struct axp288_chrg_info *info = dev;
	int i;

	for (i = 0; i < CHRG_INTR_END; i++) {
		if (info->irq[i] == irq)
			break;
	}

	if (i >= CHRG_INTR_END) {
		dev_warn(&info->pdev->dev, "spurious interrupt!!\n");
		return IRQ_NONE;
	}

	switch (i) {
	case VBUS_OV_IRQ:
		dev_dbg(&info->pdev->dev, "VBUS Over Voltage INTR\n");
		break;
	case CHARGE_DONE_IRQ:
		dev_dbg(&info->pdev->dev, "Charging Done INTR\n");
		break;
	case CHARGE_CHARGING_IRQ:
		dev_dbg(&info->pdev->dev, "Start Charging IRQ\n");
		break;
	case BAT_SAFE_QUIT_IRQ:
		dev_dbg(&info->pdev->dev,
			"Quit Safe Mode(restart timer) Charging IRQ\n");
		break;
	case BAT_SAFE_ENTER_IRQ:
		dev_dbg(&info->pdev->dev,
			"Enter Safe Mode(timer expire) Charging IRQ\n");
		break;
	case QCBTU_IRQ:
		dev_dbg(&info->pdev->dev,
			"Quit Battery Under Temperature(CHRG) INTR\n");
		break;
	case CBTU_IRQ:
		dev_dbg(&info->pdev->dev,
			"Hit Battery Under Temperature(CHRG) INTR\n");
		break;
	case QCBTO_IRQ:
		dev_dbg(&info->pdev->dev,
			"Quit Battery Over Temperature(CHRG) INTR\n");
		break;
	case CBTO_IRQ:
		dev_dbg(&info->pdev->dev,
			"Hit Battery Over Temperature(CHRG) INTR\n");
		break;
	default:
		dev_warn(&info->pdev->dev, "Spurious Interrupt!!!\n");
		goto out;
	}

	power_supply_changed(info->psy_usb);
out:
	return IRQ_HANDLED;
}