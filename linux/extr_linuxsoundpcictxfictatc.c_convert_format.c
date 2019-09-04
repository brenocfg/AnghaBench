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
struct snd_card {int /*<<< orphan*/  dev; } ;
typedef  int snd_pcm_format_t ;

/* Variables and functions */
#define  SNDRV_PCM_FORMAT_FLOAT_LE 132 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S24_3LE 130 
#define  SNDRV_PCM_FORMAT_S32_LE 129 
#define  SNDRV_PCM_FORMAT_U8 128 
 unsigned int SRC_SF_F32 ; 
 unsigned int SRC_SF_S16 ; 
 unsigned int SRC_SF_S24 ; 
 unsigned int SRC_SF_S32 ; 
 unsigned int SRC_SF_U8 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static unsigned int convert_format(snd_pcm_format_t snd_format,
				   struct snd_card *card)
{
	switch (snd_format) {
	case SNDRV_PCM_FORMAT_U8:
		return SRC_SF_U8;
	case SNDRV_PCM_FORMAT_S16_LE:
		return SRC_SF_S16;
	case SNDRV_PCM_FORMAT_S24_3LE:
		return SRC_SF_S24;
	case SNDRV_PCM_FORMAT_S32_LE:
		return SRC_SF_S32;
	case SNDRV_PCM_FORMAT_FLOAT_LE:
		return SRC_SF_F32;
	default:
		dev_err(card->dev, "not recognized snd format is %d\n",
			snd_format);
		return SRC_SF_S16;
	}
}