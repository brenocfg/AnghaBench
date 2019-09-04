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
struct lola {TYPE_1__* pcm; } ;
struct TYPE_2__ {int num_streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR1 ; 
 size_t CAPT ; 
 int /*<<< orphan*/  DIINTCTL ; 
 int /*<<< orphan*/  DINTCTL ; 
 int /*<<< orphan*/  DOINTCTL ; 
 unsigned int LOLA_DINT_CTRL ; 
 unsigned int LOLA_DINT_FIFOERR ; 
 unsigned int LOLA_DINT_GLOBAL ; 
 unsigned int LOLA_DINT_MUERR ; 
 size_t PLAY ; 
 int /*<<< orphan*/  lola_writel (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void lola_irq_enable(struct lola *chip)
{
	unsigned int val;

	/* enalbe all I/O streams */
	val = (1 << chip->pcm[PLAY].num_streams) - 1;
	lola_writel(chip, BAR1, DOINTCTL, val);
	val = (1 << chip->pcm[CAPT].num_streams) - 1;
	lola_writel(chip, BAR1, DIINTCTL, val);

	/* enable global irqs */
	val = LOLA_DINT_GLOBAL | LOLA_DINT_CTRL | LOLA_DINT_FIFOERR |
		LOLA_DINT_MUERR;
	lola_writel(chip, BAR1, DINTCTL, val);
}