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
struct hdac_device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int reg_raw_write (struct hdac_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_hdac_power_down_pm (struct hdac_device*) ; 
 int snd_hdac_power_up_pm (struct hdac_device*) ; 

int snd_hdac_regmap_write_raw(struct hdac_device *codec, unsigned int reg,
			      unsigned int val)
{
	int err;

	err = reg_raw_write(codec, reg, val);
	if (err == -EAGAIN) {
		err = snd_hdac_power_up_pm(codec);
		if (err >= 0)
			err = reg_raw_write(codec, reg, val);
		snd_hdac_power_down_pm(codec);
	}
	return err;
}