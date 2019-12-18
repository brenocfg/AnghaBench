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
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int,int,int) ; 

__attribute__((used)) static int patch_alc203(struct snd_ac97 *ac97)
{
	snd_ac97_update_bits(ac97, 0x7a, 0x400, 0x400);
	return 0;
}