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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct esschan {int /*<<< orphan*/ * apu; int /*<<< orphan*/  list; } ;
struct es1968 {int /*<<< orphan*/  substream_lock; } ;
struct TYPE_2__ {struct esschan* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct esschan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_es1968_free_apu_pair (struct es1968*,int /*<<< orphan*/ ) ; 
 struct es1968* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_es1968_playback_close(struct snd_pcm_substream *substream)
{
	struct es1968 *chip = snd_pcm_substream_chip(substream);
	struct esschan *es;

	if (substream->runtime->private_data == NULL)
		return 0;
	es = substream->runtime->private_data;
	spin_lock_irq(&chip->substream_lock);
	list_del(&es->list);
	spin_unlock_irq(&chip->substream_lock);
	snd_es1968_free_apu_pair(chip, es->apu[0]);
	kfree(es);

	return 0;
}