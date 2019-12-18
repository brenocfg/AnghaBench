#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_azf3328 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char const*,unsigned short) ; 

__attribute__((used)) static inline void
snd_azf3328_mixer_ac97_map_unsupported(const struct snd_azf3328 *chip,
				       unsigned short reg, const char *mode)
{
	/* need to add some more or less clever emulation? */
	dev_warn(chip->card->dev,
		"missing %s emulation for AC97 register 0x%02x!\n",
		mode, reg);
}