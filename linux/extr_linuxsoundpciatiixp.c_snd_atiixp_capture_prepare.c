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
struct atiixp {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {scalar_t__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_REG_CMD_INTERLEAVE_IN ; 
 int /*<<< orphan*/  CMD ; 
 scalar_t__ SNDRV_PCM_FORMAT_S16_LE ; 
 int /*<<< orphan*/  atiixp_update (struct atiixp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atiixp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_atiixp_capture_prepare(struct snd_pcm_substream *substream)
{
	struct atiixp *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	atiixp_update(chip, CMD, ATI_REG_CMD_INTERLEAVE_IN,
		      substream->runtime->format == SNDRV_PCM_FORMAT_S16_LE ?
		      ATI_REG_CMD_INTERLEAVE_IN : 0);
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}