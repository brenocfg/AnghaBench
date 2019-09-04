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
struct sbs_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int sbs_check_state (struct sbs_info*) ; 

__attribute__((used)) static irqreturn_t sbs_irq_thread(int irq, void *data)
{
	struct sbs_info *chip = data;
	int ret;

	ret = sbs_check_state(chip);

	return ret ? IRQ_HANDLED : IRQ_NONE;
}