#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {int reg_pairs_len; scalar_t__ reg_base; TYPE_2__* reg_pairs; scalar_t__ burst_read; TYPE_1__ resp; } ;
struct mt76x0_dev {TYPE_3__ mcu; } ;
struct TYPE_5__ {scalar_t__ reg; scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ get_unaligned_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76x0_read_resp_regs(struct mt76x0_dev *dev, int len)
{
	int i;
	int n = dev->mcu.reg_pairs_len;
	u8 *buf = dev->mcu.resp.buf;

	buf += 4;
	len -= 8;

	if (dev->mcu.burst_read) {
		u32 reg = dev->mcu.reg_pairs[0].reg - dev->mcu.reg_base;

		WARN_ON_ONCE(len/4 != n);
		for (i = 0; i < n; i++) {
			u32 val = get_unaligned_le32(buf + 4*i);

			dev->mcu.reg_pairs[i].reg = reg++;
			dev->mcu.reg_pairs[i].value = val;
		}
	} else {
		WARN_ON_ONCE(len/8 != n);
		for (i = 0; i < n; i++) {
			u32 reg = get_unaligned_le32(buf + 8*i) - dev->mcu.reg_base;
			u32 val = get_unaligned_le32(buf + 8*i + 4);

			WARN_ON_ONCE(dev->mcu.reg_pairs[i].reg != reg);
			dev->mcu.reg_pairs[i].value = val;
		}
	}
}