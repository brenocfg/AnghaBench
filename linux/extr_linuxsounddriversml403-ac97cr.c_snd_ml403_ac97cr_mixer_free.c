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
struct snd_ml403_ac97cr {int /*<<< orphan*/ * ac97; } ;
struct snd_ac97 {struct snd_ml403_ac97cr* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_INFO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void snd_ml403_ac97cr_mixer_free(struct snd_ac97 *ac97)
{
	struct snd_ml403_ac97cr *ml403_ac97cr = ac97->private_data;
	PDEBUG(INIT_INFO, "mixer_free():\n");
	ml403_ac97cr->ac97 = NULL;
	PDEBUG(INIT_INFO, "mixer_free(): (done)\n");
}