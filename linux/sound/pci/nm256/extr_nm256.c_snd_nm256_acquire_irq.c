#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nm256 {scalar_t__ irq; int /*<<< orphan*/  irq_mutex; int /*<<< orphan*/  irq_acks; TYPE_2__* pci; TYPE_1__* card; int /*<<< orphan*/  interrupt; } ;
struct TYPE_4__ {scalar_t__ irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nm256*) ; 

__attribute__((used)) static int snd_nm256_acquire_irq(struct nm256 *chip)
{
	mutex_lock(&chip->irq_mutex);
	if (chip->irq < 0) {
		if (request_irq(chip->pci->irq, chip->interrupt, IRQF_SHARED,
				KBUILD_MODNAME, chip)) {
			dev_err(chip->card->dev,
				"unable to grab IRQ %d\n", chip->pci->irq);
			mutex_unlock(&chip->irq_mutex);
			return -EBUSY;
		}
		chip->irq = chip->pci->irq;
	}
	chip->irq_acks++;
	mutex_unlock(&chip->irq_mutex);
	return 0;
}