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
typedef  int /*<<< orphan*/  u32 ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPE0A_EN_PORT ; 
 int /*<<< orphan*/  GPE0A_PME_B0_EN_BIT ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int0002_irq_unmask(struct irq_data *data)
{
	u32 gpe_en_reg;

	gpe_en_reg = inl(GPE0A_EN_PORT);
	gpe_en_reg |= GPE0A_PME_B0_EN_BIT;
	outl(gpe_en_reg, GPE0A_EN_PORT);
}