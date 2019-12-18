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
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 int AHB_DMAEN ; 
 int AHB_INTENLVL0 ; 
 scalar_t__ I2SAHB ; 
#define  LPAM_DMA_START 129 
#define  LPAM_DMA_STOP 128 
 TYPE_1__ idma ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void idma_control(int op)
{
	u32 val = readl(idma.regs + I2SAHB);

	spin_lock(&idma.lock);

	switch (op) {
	case LPAM_DMA_START:
		val |= (AHB_INTENLVL0 | AHB_DMAEN);
		break;
	case LPAM_DMA_STOP:
		val &= ~(AHB_INTENLVL0 | AHB_DMAEN);
		break;
	default:
		spin_unlock(&idma.lock);
		return;
	}

	writel(val, idma.regs + I2SAHB);
	spin_unlock(&idma.lock);
}