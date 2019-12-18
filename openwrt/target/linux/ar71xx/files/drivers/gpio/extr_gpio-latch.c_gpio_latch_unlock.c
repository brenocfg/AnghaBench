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
struct gpio_latch_chip {int latch_enabled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  latch_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gpio_latch_unlock(struct gpio_latch_chip *glc, bool disable)
{
	if (glc->latch_enabled)
		mutex_unlock(&glc->latch_mutex);

	if (disable)
		glc->latch_enabled = true;

	mutex_unlock(&glc->mutex);
}