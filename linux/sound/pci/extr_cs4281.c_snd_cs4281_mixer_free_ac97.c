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
struct snd_ac97 {scalar_t__ num; struct cs4281* private_data; } ;
struct cs4281 {int /*<<< orphan*/ * ac97; int /*<<< orphan*/ * ac97_secondary; } ;

/* Variables and functions */

__attribute__((used)) static void snd_cs4281_mixer_free_ac97(struct snd_ac97 *ac97)
{
	struct cs4281 *chip = ac97->private_data;
	if (ac97->num)
		chip->ac97_secondary = NULL;
	else
		chip->ac97 = NULL;
}