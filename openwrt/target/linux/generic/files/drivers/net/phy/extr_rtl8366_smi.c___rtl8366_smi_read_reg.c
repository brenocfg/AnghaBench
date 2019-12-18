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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtl8366_smi {int cmd_read; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8366_smi_read_byte0 (struct rtl8366_smi*,scalar_t__*) ; 
 int /*<<< orphan*/  rtl8366_smi_read_byte1 (struct rtl8366_smi*,scalar_t__*) ; 
 int /*<<< orphan*/  rtl8366_smi_start (struct rtl8366_smi*) ; 
 int /*<<< orphan*/  rtl8366_smi_stop (struct rtl8366_smi*) ; 
 int rtl8366_smi_write_byte (struct rtl8366_smi*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __rtl8366_smi_read_reg(struct rtl8366_smi *smi, u32 addr, u32 *data)
{
	unsigned long flags;
	u8 lo = 0;
	u8 hi = 0;
	int ret;

	spin_lock_irqsave(&smi->lock, flags);

	rtl8366_smi_start(smi);

	/* send READ command */
	ret = rtl8366_smi_write_byte(smi, smi->cmd_read);
	if (ret)
		goto out;

	/* set ADDR[7:0] */
	ret = rtl8366_smi_write_byte(smi, addr & 0xff);
	if (ret)
		goto out;

	/* set ADDR[15:8] */
	ret = rtl8366_smi_write_byte(smi, addr >> 8);
	if (ret)
		goto out;

	/* read DATA[7:0] */
	rtl8366_smi_read_byte0(smi, &lo);
	/* read DATA[15:8] */
	rtl8366_smi_read_byte1(smi, &hi);

	*data = ((u32) lo) | (((u32) hi) << 8);

	ret = 0;

 out:
	rtl8366_smi_stop(smi);
	spin_unlock_irqrestore(&smi->lock, flags);

	return ret;
}