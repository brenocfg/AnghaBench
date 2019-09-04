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
struct powertec_info {scalar_t__ base; } ;
struct expansion_card {struct powertec_info* irq_data; } ;

/* Variables and functions */
 scalar_t__ POWERTEC_INTR_CONTROL ; 
 int /*<<< orphan*/  POWERTEC_INTR_ENABLE ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
powertecscsi_irqenable(struct expansion_card *ec, int irqnr)
{
	struct powertec_info *info = ec->irq_data;
	writeb(POWERTEC_INTR_ENABLE, info->base + POWERTEC_INTR_CONTROL);
}