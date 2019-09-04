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
struct snd_bebob_stream_formation {scalar_t__ pcm; scalar_t__ midi; } ;

/* Variables and functions */
 scalar_t__ AM824_MAX_CHANNELS_FOR_MIDI ; 
 scalar_t__ AM824_MAX_CHANNELS_FOR_PCM ; 
 unsigned int ARRAY_SIZE (int*) ; 
 int ENOSYS ; 
 int* bridgeco_freq_table ; 
 int /*<<< orphan*/  memset (struct snd_bebob_stream_formation*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
parse_stream_formation(u8 *buf, unsigned int len,
		       struct snd_bebob_stream_formation *formation)
{
	unsigned int i, e, channels, format;

	/*
	 * this module can support a hierarchy combination that:
	 *  Root:	Audio and Music (0x90)
	 *  Level 1:	AM824 Compound  (0x40)
	 */
	if ((buf[0] != 0x90) || (buf[1] != 0x40))
		return -ENOSYS;

	/* check sampling rate */
	for (i = 0; i < ARRAY_SIZE(bridgeco_freq_table); i++) {
		if (buf[2] == bridgeco_freq_table[i])
			break;
	}
	if (i == ARRAY_SIZE(bridgeco_freq_table))
		return -ENOSYS;

	/* Avoid double count by different entries for the same rate. */
	memset(&formation[i], 0, sizeof(struct snd_bebob_stream_formation));

	for (e = 0; e < buf[4]; e++) {
		channels = buf[5 + e * 2];
		format = buf[6 + e * 2];

		switch (format) {
		/* IEC 60958 Conformant, currently handled as MBLA */
		case 0x00:
		/* Multi bit linear audio */
		case 0x06:	/* Raw */
			formation[i].pcm += channels;
			break;
		/* MIDI Conformant */
		case 0x0d:
			formation[i].midi += channels;
			break;
		/* IEC 61937-3 to 7 */
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		/* Multi bit linear audio */
		case 0x07:	/* DVD-Audio */
		case 0x0c:	/* High Precision */
		/* One Bit Audio */
		case 0x08:	/* (Plain) Raw */
		case 0x09:	/* (Plain) SACD */
		case 0x0a:	/* (Encoded) Raw */
		case 0x0b:	/* (Encoded) SACD */
		/* Synchronization Stream (Stereo Raw audio) */
		case 0x40:
		/* Don't care */
		case 0xff:
		default:
			return -ENOSYS;	/* not supported */
		}
	}

	if (formation[i].pcm  > AM824_MAX_CHANNELS_FOR_PCM ||
	    formation[i].midi > AM824_MAX_CHANNELS_FOR_MIDI)
		return -ENOSYS;

	return 0;
}