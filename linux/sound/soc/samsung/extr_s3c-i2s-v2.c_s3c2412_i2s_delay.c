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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct s3c_i2sv2_info {scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  snd_pcm_sframes_t ;

/* Variables and functions */
 scalar_t__ S3C2412_IISFIC ; 
 int /*<<< orphan*/  S3C2412_IISFIC_RXCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C2412_IISFIC_TXCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct s3c_i2sv2_info* to_info (struct snd_soc_dai*) ; 

__attribute__((used)) static snd_pcm_sframes_t s3c2412_i2s_delay(struct snd_pcm_substream *substream,
					   struct snd_soc_dai *dai)
{
	struct s3c_i2sv2_info *i2s = to_info(dai);
	u32 reg = readl(i2s->regs + S3C2412_IISFIC);
	snd_pcm_sframes_t delay;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		delay = S3C2412_IISFIC_TXCOUNT(reg);
	else
		delay = S3C2412_IISFIC_RXCOUNT(reg);

	return delay;
}