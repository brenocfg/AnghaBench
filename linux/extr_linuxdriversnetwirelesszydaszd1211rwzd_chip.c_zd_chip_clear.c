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
struct zd_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rf; int /*<<< orphan*/  usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_ASSERT (int) ; 
 int /*<<< orphan*/  ZD_MEMCLEAR (struct zd_chip*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_rf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_usb_clear (int /*<<< orphan*/ *) ; 

void zd_chip_clear(struct zd_chip *chip)
{
	ZD_ASSERT(!mutex_is_locked(&chip->mutex));
	zd_usb_clear(&chip->usb);
	zd_rf_clear(&chip->rf);
	mutex_destroy(&chip->mutex);
	ZD_MEMCLEAR(chip, sizeof(*chip));
}