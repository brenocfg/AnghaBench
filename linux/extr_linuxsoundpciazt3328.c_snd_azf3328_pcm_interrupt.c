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
typedef  int u8 ;
struct snd_azf3328_codec_data {int /*<<< orphan*/  name; scalar_t__ substream; int /*<<< orphan*/  lock; } ;
struct snd_azf3328 {TYPE_1__* card; } ;
typedef  enum snd_azf3328_codec_type { ____Placeholder_snd_azf3328_codec_type } snd_azf3328_codec_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZF_CODEC_I2S_OUT ; 
 int AZF_CODEC_PLAYBACK ; 
 int /*<<< orphan*/  IDX_IO_CODEC_DMA_CURRPOS ; 
 int /*<<< orphan*/  IDX_IO_CODEC_IRQTYPE ; 
 int IRQ_SOMETHING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int snd_azf3328_codec_inb (struct snd_azf3328_codec_data const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_azf3328_codec_inl (struct snd_azf3328_codec_data const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_azf3328_codec_outb (struct snd_azf3328_codec_data const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_azf3328_irq_log_unknown_type (struct snd_azf3328*,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
snd_azf3328_pcm_interrupt(struct snd_azf3328 *chip,
			  const struct snd_azf3328_codec_data *first_codec,
			  u8 status
)
{
	u8 which;
	enum snd_azf3328_codec_type codec_type;
	const struct snd_azf3328_codec_data *codec = first_codec;

	for (codec_type = AZF_CODEC_PLAYBACK;
		 codec_type <= AZF_CODEC_I2S_OUT;
			 ++codec_type, ++codec) {

		/* skip codec if there's no interrupt for it */
		if (!(status & (1 << codec_type)))
			continue;

		spin_lock(codec->lock);
		which = snd_azf3328_codec_inb(codec, IDX_IO_CODEC_IRQTYPE);
		/* ack all IRQ types immediately */
		snd_azf3328_codec_outb(codec, IDX_IO_CODEC_IRQTYPE, which);
		spin_unlock(codec->lock);

		if (codec->substream) {
			snd_pcm_period_elapsed(codec->substream);
			dev_dbg(chip->card->dev, "%s period done (#%x), @ %x\n",
				codec->name,
				which,
				snd_azf3328_codec_inl(
					codec, IDX_IO_CODEC_DMA_CURRPOS));
		} else
			dev_warn(chip->card->dev, "irq handler problem!\n");
		if (which & IRQ_SOMETHING)
			snd_azf3328_irq_log_unknown_type(chip, which);
	}
}