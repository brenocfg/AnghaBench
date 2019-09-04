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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct mt76x2_dev {TYPE_1__ mcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_SELECT ; 
 int mt76pci_load_firmware (struct mt76x2_dev*) ; 
 int mt76pci_load_rom_patch (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_mcu_function_select (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int mt76x2_mcu_init(struct mt76x2_dev *dev)
{
	int ret;

	mutex_init(&dev->mcu.mutex);

	ret = mt76pci_load_rom_patch(dev);
	if (ret)
		return ret;

	ret = mt76pci_load_firmware(dev);
	if (ret)
		return ret;

	mt76x2_mcu_function_select(dev, Q_SELECT, 1);
	return 0;
}