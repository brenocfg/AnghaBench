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
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_INTERRUPT ; 
 int /*<<< orphan*/  HWINT_ENABLED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zd_iowrite32_locked (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int zd_chip_enable_hwint(struct zd_chip *chip)
{
	int r;

	mutex_lock(&chip->mutex);
	r = zd_iowrite32_locked(chip, HWINT_ENABLED, CR_INTERRUPT);
	mutex_unlock(&chip->mutex);
	return r;
}