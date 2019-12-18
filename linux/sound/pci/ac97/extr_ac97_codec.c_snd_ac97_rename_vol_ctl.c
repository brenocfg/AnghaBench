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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ac97_rename_ctl (struct snd_ac97*,char const*,char const*,char*) ; 

__attribute__((used)) static void snd_ac97_rename_vol_ctl(struct snd_ac97 *ac97, const char *src,
				    const char *dst)
{
	snd_ac97_rename_ctl(ac97, src, dst, "Switch");
	snd_ac97_rename_ctl(ac97, src, dst, "Volume");
}