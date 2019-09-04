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
typedef  int u8 ;
struct snd_oxfw_stream_formation {scalar_t__ pcm; unsigned int midi; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 scalar_t__ AM824_MAX_CHANNELS_FOR_MIDI ; 
 scalar_t__ AM824_MAX_CHANNELS_FOR_PCM ; 
 unsigned int ARRAY_SIZE (int*) ; 
 int ENOSYS ; 
 int* avc_stream_rate_table ; 
 int /*<<< orphan*/  memset (struct snd_oxfw_stream_formation*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * oxfw_rate_table ; 

int snd_oxfw_stream_parse_format(u8 *format,
				 struct snd_oxfw_stream_formation *formation)
{
	unsigned int i, e, channels, type;

	memset(formation, 0, sizeof(struct snd_oxfw_stream_formation));

	/*
	 * this module can support a hierarchy combination that:
	 *  Root:	Audio and Music (0x90)
	 *  Level 1:	AM824 Compound  (0x40)
	 */
	if ((format[0] != 0x90) || (format[1] != 0x40))
		return -ENOSYS;

	/* check the sampling rate */
	for (i = 0; i < ARRAY_SIZE(avc_stream_rate_table); i++) {
		if (format[2] == avc_stream_rate_table[i])
			break;
	}
	if (i == ARRAY_SIZE(avc_stream_rate_table))
		return -ENOSYS;

	formation->rate = oxfw_rate_table[i];

	for (e = 0; e < format[4]; e++) {
		channels = format[5 + e * 2];
		type = format[6 + e * 2];

		switch (type) {
		/* IEC 60958 Conformant, currently handled as MBLA */
		case 0x00:
		/* Multi Bit Linear Audio (Raw) */
		case 0x06:
			formation->pcm += channels;
			break;
		/* MIDI Conformant */
		case 0x0d:
			formation->midi = channels;
			break;
		/* IEC 61937-3 to 7 */
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		/* Multi Bit Linear Audio */
		case 0x07:	/* DVD-Audio */
		case 0x0c:	/* High Precision */
		/* One Bit Audio */
		case 0x08:	/* (Plain) Raw */
		case 0x09:	/* (Plain) SACD */
		case 0x0a:	/* (Encoded) Raw */
		case 0x0b:	/* (Encoded) SACD */
		/* SMPTE Time-Code conformant */
		case 0x0e:
		/* Sample Count */
		case 0x0f:
		/* Anciliary Data */
		case 0x10:
		/* Synchronization Stream (Stereo Raw audio) */
		case 0x40:
		/* Don't care */
		case 0xff:
		default:
			return -ENOSYS;	/* not supported */
		}
	}

	if (formation->pcm  > AM824_MAX_CHANNELS_FOR_PCM ||
	    formation->midi > AM824_MAX_CHANNELS_FOR_MIDI)
		return -ENOSYS;

	return 0;
}