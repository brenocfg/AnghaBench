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
 int reg_raw_read (struct hdac_device*,unsigned int,unsigned int*,int) ; 
 int /*<<< orphan*/  snd_hdac_power_down_pm (struct hdac_device*) ; 
 int snd_hdac_power_up_pm (struct hdac_device*) ; 

__attribute__((used)) static int __snd_hdac_regmap_read_raw(struct hdac_device *codec,
				      unsigned int reg, unsigned int *val,
				      bool uncached)
{
	int err;

	err = reg_raw_read(codec, reg, val, uncached);
	if (err == -EAGAIN) {
		err = snd_hdac_power_up_pm(codec);
		if (err >= 0)
			err = reg_raw_read(codec, reg, val, uncached);
		snd_hdac_power_down_pm(codec);
	}
	return err;
}