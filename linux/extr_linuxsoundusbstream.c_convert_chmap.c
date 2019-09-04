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
struct snd_pcm_chmap_elem {unsigned int* map; int channels; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  SNDRV_CHMAP_BC 154 
#define  SNDRV_CHMAP_FC 153 
#define  SNDRV_CHMAP_FL 152 
#define  SNDRV_CHMAP_FLC 151 
#define  SNDRV_CHMAP_FR 150 
#define  SNDRV_CHMAP_FRC 149 
#define  SNDRV_CHMAP_LFE 148 
#define  SNDRV_CHMAP_LLFE 147 
 unsigned int SNDRV_CHMAP_MONO ; 
#define  SNDRV_CHMAP_RC 146 
#define  SNDRV_CHMAP_RL 145 
#define  SNDRV_CHMAP_RLC 144 
#define  SNDRV_CHMAP_RLFE 143 
#define  SNDRV_CHMAP_RR 142 
#define  SNDRV_CHMAP_RRC 141 
#define  SNDRV_CHMAP_SL 140 
#define  SNDRV_CHMAP_SR 139 
#define  SNDRV_CHMAP_TC 138 
#define  SNDRV_CHMAP_TFC 137 
#define  SNDRV_CHMAP_TFL 136 
#define  SNDRV_CHMAP_TFLC 135 
#define  SNDRV_CHMAP_TFR 134 
#define  SNDRV_CHMAP_TFRC 133 
#define  SNDRV_CHMAP_TRC 132 
#define  SNDRV_CHMAP_TRL 131 
#define  SNDRV_CHMAP_TRR 130 
#define  SNDRV_CHMAP_TSL 129 
#define  SNDRV_CHMAP_TSR 128 
 unsigned int SNDRV_CHMAP_UNKNOWN ; 
 int UAC_VERSION_2 ; 
 struct snd_pcm_chmap_elem* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_pcm_chmap_elem *convert_chmap(int channels, unsigned int bits,
						int protocol)
{
	static unsigned int uac1_maps[] = {
		SNDRV_CHMAP_FL,		/* left front */
		SNDRV_CHMAP_FR,		/* right front */
		SNDRV_CHMAP_FC,		/* center front */
		SNDRV_CHMAP_LFE,	/* LFE */
		SNDRV_CHMAP_SL,		/* left surround */
		SNDRV_CHMAP_SR,		/* right surround */
		SNDRV_CHMAP_FLC,	/* left of center */
		SNDRV_CHMAP_FRC,	/* right of center */
		SNDRV_CHMAP_RC,		/* surround */
		SNDRV_CHMAP_SL,		/* side left */
		SNDRV_CHMAP_SR,		/* side right */
		SNDRV_CHMAP_TC,		/* top */
		0 /* terminator */
	};
	static unsigned int uac2_maps[] = {
		SNDRV_CHMAP_FL,		/* front left */
		SNDRV_CHMAP_FR,		/* front right */
		SNDRV_CHMAP_FC,		/* front center */
		SNDRV_CHMAP_LFE,	/* LFE */
		SNDRV_CHMAP_RL,		/* back left */
		SNDRV_CHMAP_RR,		/* back right */
		SNDRV_CHMAP_FLC,	/* front left of center */
		SNDRV_CHMAP_FRC,	/* front right of center */
		SNDRV_CHMAP_RC,		/* back center */
		SNDRV_CHMAP_SL,		/* side left */
		SNDRV_CHMAP_SR,		/* side right */
		SNDRV_CHMAP_TC,		/* top center */
		SNDRV_CHMAP_TFL,	/* top front left */
		SNDRV_CHMAP_TFC,	/* top front center */
		SNDRV_CHMAP_TFR,	/* top front right */
		SNDRV_CHMAP_TRL,	/* top back left */
		SNDRV_CHMAP_TRC,	/* top back center */
		SNDRV_CHMAP_TRR,	/* top back right */
		SNDRV_CHMAP_TFLC,	/* top front left of center */
		SNDRV_CHMAP_TFRC,	/* top front right of center */
		SNDRV_CHMAP_LLFE,	/* left LFE */
		SNDRV_CHMAP_RLFE,	/* right LFE */
		SNDRV_CHMAP_TSL,	/* top side left */
		SNDRV_CHMAP_TSR,	/* top side right */
		SNDRV_CHMAP_BC,		/* bottom center */
		SNDRV_CHMAP_RLC,	/* back left of center */
		SNDRV_CHMAP_RRC,	/* back right of center */
		0 /* terminator */
	};
	struct snd_pcm_chmap_elem *chmap;
	const unsigned int *maps;
	int c;

	if (channels > ARRAY_SIZE(chmap->map))
		return NULL;

	chmap = kzalloc(sizeof(*chmap), GFP_KERNEL);
	if (!chmap)
		return NULL;

	maps = protocol == UAC_VERSION_2 ? uac2_maps : uac1_maps;
	chmap->channels = channels;
	c = 0;

	if (bits) {
		for (; bits && *maps; maps++, bits >>= 1)
			if (bits & 1)
				chmap->map[c++] = *maps;
	} else {
		/* If we're missing wChannelConfig, then guess something
		    to make sure the channel map is not skipped entirely */
		if (channels == 1)
			chmap->map[c++] = SNDRV_CHMAP_MONO;
		else
			for (; c < channels && *maps; maps++)
				chmap->map[c++] = *maps;
	}

	for (; c < channels; c++)
		chmap->map[c] = SNDRV_CHMAP_UNKNOWN;

	return chmap;
}