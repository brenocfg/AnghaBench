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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pclkdiv_lock; } ;
struct TYPE_4__ {TYPE_1__ es1370; } ;
struct ensoniq {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  mode; TYPE_2__ u; int /*<<< orphan*/ * capture_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_MODE_CAPTURE ; 
 struct ensoniq* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ensoniq_capture_close(struct snd_pcm_substream *substream)
{
	struct ensoniq *ensoniq = snd_pcm_substream_chip(substream);

	ensoniq->capture_substream = NULL;
	spin_lock_irq(&ensoniq->reg_lock);
#ifdef CHIP1370
	ensoniq->u.es1370.pclkdiv_lock &= ~ES_MODE_CAPTURE;
#endif
	ensoniq->mode &= ~ES_MODE_CAPTURE;
	spin_unlock_irq(&ensoniq->reg_lock);
	return 0;
}