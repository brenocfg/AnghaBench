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
struct snd_pcm_substream {int dummy; } ;
struct ensoniq {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  mode; int /*<<< orphan*/ * playback2_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_MODE_PLAY2 ; 
 struct ensoniq* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ensoniq_playback2_close(struct snd_pcm_substream *substream)
{
	struct ensoniq *ensoniq = snd_pcm_substream_chip(substream);

	ensoniq->playback2_substream = NULL;
	spin_lock_irq(&ensoniq->reg_lock);
#ifdef CHIP1370
	ensoniq->u.es1370.pclkdiv_lock &= ~ES_MODE_PLAY2;
#endif
	ensoniq->mode &= ~ES_MODE_PLAY2;
	spin_unlock_irq(&ensoniq->reg_lock);
	return 0;
}