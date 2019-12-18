#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* card; } ;
typedef  TYPE_2__ vortex_t ;
typedef  int snd_pcm_format_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SNDRV_PCM_FORMAT_A_LAW 134 
#define  SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE 133 
#define  SNDRV_PCM_FORMAT_MU_LAW 132 
#define  SNDRV_PCM_FORMAT_S16_BE 131 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_SPECIAL 129 
#define  SNDRV_PCM_FORMAT_U8 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vortex_alsafmt_aspfmt(snd_pcm_format_t alsafmt, vortex_t *v)
{
	int fmt;

	switch (alsafmt) {
	case SNDRV_PCM_FORMAT_U8:
		fmt = 0x1;
		break;
	case SNDRV_PCM_FORMAT_MU_LAW:
		fmt = 0x2;
		break;
	case SNDRV_PCM_FORMAT_A_LAW:
		fmt = 0x3;
		break;
	case SNDRV_PCM_FORMAT_SPECIAL:
		fmt = 0x4;	/* guess. */
		break;
	case SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE:
		fmt = 0x5;	/* guess. */
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		fmt = 0x8;
		break;
	case SNDRV_PCM_FORMAT_S16_BE:
		fmt = 0x9;	/* check this... */
		break;
	default:
		fmt = 0x8;
		dev_err(v->card->dev,
			"format unsupported %d\n", alsafmt);
		break;
	}
	return fmt;
}