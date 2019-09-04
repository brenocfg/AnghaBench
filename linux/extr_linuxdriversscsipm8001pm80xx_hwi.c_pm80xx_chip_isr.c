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
typedef  int /*<<< orphan*/  u8 ;
struct pm8001_hba_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  pm80xx_chip_interrupt_disable (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm80xx_chip_interrupt_enable (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_oq (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
pm80xx_chip_isr(struct pm8001_hba_info *pm8001_ha, u8 vec)
{
	pm80xx_chip_interrupt_disable(pm8001_ha, vec);
	process_oq(pm8001_ha, vec);
	pm80xx_chip_interrupt_enable(pm8001_ha, vec);
	return IRQ_HANDLED;
}