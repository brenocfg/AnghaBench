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
struct mt76x2_dev {int dummy; } ;

/* Variables and functions */
 int mt76x2_efuse_read (struct mt76x2_dev*,int,void*) ; 

__attribute__((used)) static int
mt76x2_get_efuse_data(struct mt76x2_dev *dev, void *buf, int len)
{
	int ret, i;

	for (i = 0; i + 16 <= len; i += 16) {
		ret = mt76x2_efuse_read(dev, i, buf + i);
		if (ret)
			return ret;
	}

	return 0;
}