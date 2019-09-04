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
typedef  int u32 ;
struct aac_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  OutboundQueue; int /*<<< orphan*/  ODR; } ;

/* Variables and functions */
 int DoorBellAdapterNormRespReady ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 TYPE_1__ MUnit ; 
 int aac_intr_normal (struct aac_dev*,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int rx_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_writel (struct aac_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t aac_rx_intr_message(int irq, void *dev_id)
{
	int isAif, isFastResponse, isSpecial;
	struct aac_dev *dev = dev_id;
	u32 Index = rx_readl(dev, MUnit.OutboundQueue);
	if (unlikely(Index == 0xFFFFFFFFL))
		Index = rx_readl(dev, MUnit.OutboundQueue);
	if (likely(Index != 0xFFFFFFFFL)) {
		do {
			isAif = isFastResponse = isSpecial = 0;
			if (Index & 0x00000002L) {
				isAif = 1;
				if (Index == 0xFFFFFFFEL)
					isSpecial = 1;
				Index &= ~0x00000002L;
			} else {
				if (Index & 0x00000001L)
					isFastResponse = 1;
				Index >>= 2;
			}
			if (!isSpecial) {
				if (unlikely(aac_intr_normal(dev,
						Index, isAif,
						isFastResponse, NULL))) {
					rx_writel(dev,
						MUnit.OutboundQueue,
						Index);
					rx_writel(dev,
						MUnit.ODR,
						DoorBellAdapterNormRespReady);
				}
			}
			Index = rx_readl(dev, MUnit.OutboundQueue);
		} while (Index != 0xFFFFFFFFL);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}