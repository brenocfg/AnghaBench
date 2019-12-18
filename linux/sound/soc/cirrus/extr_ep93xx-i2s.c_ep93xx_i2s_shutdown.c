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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct ep93xx_i2s_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ep93xx_i2s_disable (struct ep93xx_i2s_info*,int /*<<< orphan*/ ) ; 
 struct ep93xx_i2s_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void ep93xx_i2s_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct ep93xx_i2s_info *info = snd_soc_dai_get_drvdata(dai);

	ep93xx_i2s_disable(info, substream->stream);
}