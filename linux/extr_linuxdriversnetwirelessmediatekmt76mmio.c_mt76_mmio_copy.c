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
struct mt76_dev {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iowrite32_copy (scalar_t__,void const*,int) ; 

__attribute__((used)) static void mt76_mmio_copy(struct mt76_dev *dev, u32 offset, const void *data,
			   int len)
{
	__iowrite32_copy(dev->regs + offset, data, len >> 2);
}