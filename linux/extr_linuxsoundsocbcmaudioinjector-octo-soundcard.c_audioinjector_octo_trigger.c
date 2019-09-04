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
struct snd_pcm_substream {int dummy; } ;
typedef  int /*<<< orphan*/  mult ;
struct TYPE_2__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  ndescs; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  audioinjector_octo_rate ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mult_gpios ; 
 int /*<<< orphan*/  non_stop_clocks ; 

__attribute__((used)) static int audioinjector_octo_trigger(struct snd_pcm_substream *substream,
								int cmd){
	int mult[4];

	memset(mult, 0, sizeof(mult));

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (!non_stop_clocks)
			break;
		/* Drop through... */
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		switch (audioinjector_octo_rate) {
		case 96000:
			mult[3] = 1;
		case 88200:
			mult[1] = 1;
			mult[2] = 1;
			break;
		case 48000:
			mult[3] = 1;
		case 44100:
			mult[2] = 1;
			break;
		case 32000:
			mult[3] = 1;
		case 29400:
			mult[0] = 1;
			mult[1] = 1;
			break;
		case 24000:
			mult[3] = 1;
		case 22050:
			mult[1] = 1;
			break;
		case 16000:
			mult[3] = 1;
		case 14700:
			mult[0] = 1;
			break;
		case 8000:
			mult[3] = 1;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}
	gpiod_set_array_value_cansleep(mult_gpios->ndescs, mult_gpios->desc,
									mult);

	return 0;
}