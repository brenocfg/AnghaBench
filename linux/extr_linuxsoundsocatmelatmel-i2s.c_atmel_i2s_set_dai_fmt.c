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
struct snd_soc_dai {int dummy; } ;
struct atmel_i2s_dev {unsigned int fmt; } ;

/* Variables and functions */
 struct atmel_i2s_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int atmel_i2s_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct atmel_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	dev->fmt = fmt;
	return 0;
}