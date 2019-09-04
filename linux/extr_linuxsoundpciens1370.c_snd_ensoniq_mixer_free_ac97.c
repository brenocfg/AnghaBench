#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_ac97 {struct ensoniq* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ac97; } ;
struct TYPE_4__ {TYPE_1__ es1371; } ;
struct ensoniq {TYPE_2__ u; } ;

/* Variables and functions */

__attribute__((used)) static void snd_ensoniq_mixer_free_ac97(struct snd_ac97 *ac97)
{
	struct ensoniq *ensoniq = ac97->private_data;
	ensoniq->u.es1371.ac97 = NULL;
}