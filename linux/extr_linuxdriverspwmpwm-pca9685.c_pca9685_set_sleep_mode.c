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
struct pca9685 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE1_SLEEP ; 
 int /*<<< orphan*/  PCA9685_MODE1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pca9685_set_sleep_mode(struct pca9685 *pca, bool enable)
{
	regmap_update_bits(pca->regmap, PCA9685_MODE1,
			   MODE1_SLEEP, enable ? MODE1_SLEEP : 0);
	if (!enable) {
		/* Wait 500us for the oscillator to be back up */
		udelay(500);
	}
}