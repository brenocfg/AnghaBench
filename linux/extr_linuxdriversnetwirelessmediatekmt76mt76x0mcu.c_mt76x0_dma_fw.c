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
typedef  scalar_t__ u32 ;
struct mt76x0_dma_buf {int dummy; } ;
struct mt76x0_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_FW_URB_MAX_PAYLOAD ; 
 int __mt76x0_dma_fw (struct mt76x0_dev*,struct mt76x0_dma_buf*,void const*,int,scalar_t__) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mt76x0_dma_fw(struct mt76x0_dev *dev, struct mt76x0_dma_buf *dma_buf,
	       const void *data, int len, u32 dst_addr)
{
	int n, ret;

	if (len == 0)
		return 0;

	n = min(MCU_FW_URB_MAX_PAYLOAD, len);
	ret = __mt76x0_dma_fw(dev, dma_buf, data, n, dst_addr);
	if (ret)
		return ret;

#if 0
	if (!mt76_poll_msec(dev, MT_MCU_COM_REG1, BIT(31), BIT(31), 500))
		return -ETIMEDOUT;
#endif

	return mt76x0_dma_fw(dev, dma_buf, data + n, len - n, dst_addr + n);
}