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
struct hdac_device {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int hda_reg_read (struct hdac_device*,unsigned int,unsigned int*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int reg_raw_read(struct hdac_device *codec, unsigned int reg,
			unsigned int *val, bool uncached)
{
	if (uncached || !codec->regmap)
		return hda_reg_read(codec, reg, val);
	else
		return regmap_read(codec->regmap, reg, val);
}