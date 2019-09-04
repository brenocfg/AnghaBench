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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt76x0_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MT_EE_PHYSICAL_READ ; 
 int MT_EE_USAGE_MAP_START ; 
 int MT_EFUSE_USAGE_MAP_SIZE ; 
 int MT_MAP_READS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mt76x0_efuse_read (struct mt76x0_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76x0_efuse_physical_size_check(struct mt76x0_dev *dev)
{
	u8 data[MT_MAP_READS * 16];
	int ret, i;
	u32 start = 0, end = 0, cnt_free;

	for (i = 0; i < MT_MAP_READS; i++) {
		ret = mt76x0_efuse_read(dev, MT_EE_USAGE_MAP_START + i * 16,
					 data + i * 16, MT_EE_PHYSICAL_READ);
		if (ret)
			return ret;
	}

	for (i = 0; i < MT_EFUSE_USAGE_MAP_SIZE; i++)
		if (!data[i]) {
			if (!start)
				start = MT_EE_USAGE_MAP_START + i;
			end = MT_EE_USAGE_MAP_START + i;
		}
	cnt_free = end - start + 1;

	if (MT_EFUSE_USAGE_MAP_SIZE - cnt_free < 5) {
		dev_err(dev->mt76.dev, "Error: your device needs default EEPROM file and this driver doesn't support it!\n");
		return -EINVAL;
	}

	return 0;
}