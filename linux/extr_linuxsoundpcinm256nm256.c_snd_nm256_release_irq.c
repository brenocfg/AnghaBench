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
struct nm256 {scalar_t__ irq_acks; int irq; int /*<<< orphan*/  irq_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct nm256*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_nm256_release_irq(struct nm256 *chip)
{
	mutex_lock(&chip->irq_mutex);
	if (chip->irq_acks > 0)
		chip->irq_acks--;
	if (chip->irq_acks == 0 && chip->irq >= 0) {
		free_irq(chip->irq, chip);
		chip->irq = -1;
	}
	mutex_unlock(&chip->irq_mutex);
}