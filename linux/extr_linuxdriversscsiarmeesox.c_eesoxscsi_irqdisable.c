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
struct expansion_card {scalar_t__ irq_data; } ;
struct eesoxscsi_info {int /*<<< orphan*/  ctl_port; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  EESOX_INTR_ENABLE ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
eesoxscsi_irqdisable(struct expansion_card *ec, int irqnr)
{
	struct eesoxscsi_info *info = (struct eesoxscsi_info *)ec->irq_data;

	info->control &= ~EESOX_INTR_ENABLE;

	writeb(info->control, info->ctl_port);
}