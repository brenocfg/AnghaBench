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
 int __snd_hdac_regmap_read_raw (struct hdac_device*,unsigned int,unsigned int*,int) ; 

int snd_hdac_regmap_read_raw_uncached(struct hdac_device *codec,
				      unsigned int reg, unsigned int *val)
{
	return __snd_hdac_regmap_read_raw(codec, reg, val, true);
}