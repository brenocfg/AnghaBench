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
struct snd_ad1889 {int dummy; } ;
struct snd_ac97 {struct snd_ad1889* private_data; } ;

/* Variables and functions */
 scalar_t__ AD_AC97_BASE ; 
 int /*<<< orphan*/  ad1889_writew (struct snd_ad1889*,scalar_t__,unsigned short) ; 

__attribute__((used)) static void
snd_ad1889_ac97_write(struct snd_ac97 *ac97, unsigned short reg, unsigned short val)
{
	struct snd_ad1889 *chip = ac97->private_data;
	ad1889_writew(chip, AD_AC97_BASE + reg, val);
}