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
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_reg_wr (struct mt76_dev*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mt76_mmio_wr(struct mt76_dev *dev, u32 offset, u32 val)
{
	trace_reg_wr(dev, offset, val);
	iowrite32(val, dev->regs + offset);
}