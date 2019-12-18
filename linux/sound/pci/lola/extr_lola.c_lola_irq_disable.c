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
 int /*<<< orphan*/  BAR1 ; 
 int /*<<< orphan*/  DIINTCTL ; 
 int /*<<< orphan*/  DINTCTL ; 
 int /*<<< orphan*/  DOINTCTL ; 
 int /*<<< orphan*/  lola_writel (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lola_irq_disable(struct lola *chip)
{
	lola_writel(chip, BAR1, DINTCTL, 0);
	lola_writel(chip, BAR1, DIINTCTL, 0);
	lola_writel(chip, BAR1, DOINTCTL, 0);
}