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
struct lola {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lola_irq_disable (struct lola*) ; 
 int /*<<< orphan*/  stop_corb_rirb (struct lola*) ; 

__attribute__((used)) static void lola_stop_hw(struct lola *chip)
{
	stop_corb_rirb(chip);
	lola_irq_disable(chip);
}