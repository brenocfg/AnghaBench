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

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
#define  TPACPI_BRGHT_MODE_EC 130 
#define  TPACPI_BRGHT_MODE_ECNVRAM 129 
#define  TPACPI_BRGHT_MODE_UCMS_STEP 128 
 int /*<<< orphan*/  TPACPI_DBG_BRGHT ; 
 unsigned int bright_maxlvl ; 
 int brightness_mode ; 
 int /*<<< orphan*/  brightness_mutex ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tpacpi_brightness_set_ec (unsigned int) ; 
 int tpacpi_brightness_set_ucmsstep (unsigned int) ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int brightness_set(unsigned int value)
{
	int res;

	if (value > bright_maxlvl)
		return -EINVAL;

	vdbg_printk(TPACPI_DBG_BRGHT,
			"set backlight level to %d\n", value);

	res = mutex_lock_killable(&brightness_mutex);
	if (res < 0)
		return res;

	switch (brightness_mode) {
	case TPACPI_BRGHT_MODE_EC:
	case TPACPI_BRGHT_MODE_ECNVRAM:
		res = tpacpi_brightness_set_ec(value);
		break;
	case TPACPI_BRGHT_MODE_UCMS_STEP:
		res = tpacpi_brightness_set_ucmsstep(value);
		break;
	default:
		res = -ENXIO;
	}

	mutex_unlock(&brightness_mutex);
	return res;
}