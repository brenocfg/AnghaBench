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
typedef  int u8 ;
typedef  int u32 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_SUBID ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_ioread32_locked (struct zd_chip*,int*,int /*<<< orphan*/ ) ; 

int zd_read_regdomain(struct zd_chip *chip, u8 *regdomain)
{
	int r;
	u32 value;

	mutex_lock(&chip->mutex);
	r = zd_ioread32_locked(chip, &value, E2P_SUBID);
	mutex_unlock(&chip->mutex);
	if (r)
		return r;

	*regdomain = value >> 16;
	dev_dbg_f(zd_chip_dev(chip), "regdomain: %#04x\n", *regdomain);

	return 0;
}