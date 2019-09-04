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
struct atiixp {int /*<<< orphan*/  reg_lock; scalar_t__ spdif_over_aclink; } ;
struct TYPE_2__ {scalar_t__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_REG_CMD_INTERLEAVE_OUT ; 
 int /*<<< orphan*/  ATI_REG_CMD_INTERLEAVE_SPDF ; 
 int /*<<< orphan*/  ATI_REG_CMD_SPDF_CONFIG_01 ; 
 int /*<<< orphan*/  ATI_REG_CMD_SPDF_CONFIG_MASK ; 
 unsigned int ATI_REG_OUT_DMA_SLOT_BIT (int) ; 
 unsigned int ATI_REG_OUT_DMA_SLOT_MASK ; 
 int ATI_REG_OUT_DMA_THRESHOLD_SHIFT ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  OUT_DMA_SLOT ; 
 scalar_t__ SNDRV_PCM_FORMAT_S16_LE ; 
 unsigned int atiixp_read (struct atiixp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_update (struct atiixp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp*,int /*<<< orphan*/ ,unsigned int) ; 
 struct atiixp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_atiixp_spdif_prepare(struct snd_pcm_substream *substream)
{
	struct atiixp *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	if (chip->spdif_over_aclink) {
		unsigned int data;
		/* enable slots 10/11 */
		atiixp_update(chip, CMD, ATI_REG_CMD_SPDF_CONFIG_MASK,
			      ATI_REG_CMD_SPDF_CONFIG_01);
		data = atiixp_read(chip, OUT_DMA_SLOT) & ~ATI_REG_OUT_DMA_SLOT_MASK;
		data |= ATI_REG_OUT_DMA_SLOT_BIT(10) |
			ATI_REG_OUT_DMA_SLOT_BIT(11);
		data |= 0x04 << ATI_REG_OUT_DMA_THRESHOLD_SHIFT;
		atiixp_write(chip, OUT_DMA_SLOT, data);
		atiixp_update(chip, CMD, ATI_REG_CMD_INTERLEAVE_OUT,
			      substream->runtime->format == SNDRV_PCM_FORMAT_S16_LE ?
			      ATI_REG_CMD_INTERLEAVE_OUT : 0);
	} else {
		atiixp_update(chip, CMD, ATI_REG_CMD_SPDF_CONFIG_MASK, 0);
		atiixp_update(chip, CMD, ATI_REG_CMD_INTERLEAVE_SPDF, 0);
	}
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}