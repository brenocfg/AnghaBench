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
struct snd_device {struct snd_at73c213* device_data; } ;
struct snd_at73c213 {int irq; TYPE_1__* ssc; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  CR_TXDIS ; 
 int /*<<< orphan*/  SSC_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct snd_at73c213*) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_at73c213_dev_free(struct snd_device *device)
{
	struct snd_at73c213 *chip = device->device_data;

	ssc_writel(chip->ssc->regs, CR, SSC_BIT(CR_TXDIS));
	if (chip->irq >= 0) {
		free_irq(chip->irq, chip);
		chip->irq = -1;
	}

	return 0;
}