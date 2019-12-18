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
 int hda_reg_write (struct hdac_device*,unsigned int,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int reg_raw_write(struct hdac_device *codec, unsigned int reg,
			 unsigned int val)
{
	if (!codec->regmap)
		return hda_reg_write(codec, reg, val);
	else
		return regmap_write(codec->regmap, reg, val);
}