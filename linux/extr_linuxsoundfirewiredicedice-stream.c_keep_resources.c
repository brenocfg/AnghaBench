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
struct snd_dice {int /*<<< orphan*/  unit; struct fw_iso_resources* rx_resources; struct amdtp_stream* rx_stream; struct fw_iso_resources* tx_resources; struct amdtp_stream* tx_stream; } ;
struct fw_iso_resources {int dummy; } ;
struct amdtp_stream {int dummy; } ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;
struct TYPE_2__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int amdtp_am824_set_parameters (struct amdtp_stream*,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  amdtp_am824_set_pcm_position (struct amdtp_stream*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (struct amdtp_stream*) ; 
 int fw_iso_resources_allocate (struct fw_iso_resources*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* fw_parent_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keep_resources(struct snd_dice *dice,
			  enum amdtp_stream_direction dir, unsigned int index,
			  unsigned int rate, unsigned int pcm_chs,
			  unsigned int midi_ports)
{
	struct amdtp_stream *stream;
	struct fw_iso_resources *resources;
	bool double_pcm_frames;
	unsigned int i;
	int err;

	if (dir == AMDTP_IN_STREAM) {
		stream = &dice->tx_stream[index];
		resources = &dice->tx_resources[index];
	} else {
		stream = &dice->rx_stream[index];
		resources = &dice->rx_resources[index];
	}

	/*
	 * At 176.4/192.0 kHz, Dice has a quirk to transfer two PCM frames in
	 * one data block of AMDTP packet. Thus sampling transfer frequency is
	 * a half of PCM sampling frequency, i.e. PCM frames at 192.0 kHz are
	 * transferred on AMDTP packets at 96 kHz. Two successive samples of a
	 * channel are stored consecutively in the packet. This quirk is called
	 * as 'Dual Wire'.
	 * For this quirk, blocking mode is required and PCM buffer size should
	 * be aligned to SYT_INTERVAL.
	 */
	double_pcm_frames = rate > 96000;
	if (double_pcm_frames) {
		rate /= 2;
		pcm_chs *= 2;
	}

	err = amdtp_am824_set_parameters(stream, rate, pcm_chs, midi_ports,
					 double_pcm_frames);
	if (err < 0)
		return err;

	if (double_pcm_frames) {
		pcm_chs /= 2;

		for (i = 0; i < pcm_chs; i++) {
			amdtp_am824_set_pcm_position(stream, i, i * 2);
			amdtp_am824_set_pcm_position(stream, i + pcm_chs,
						     i * 2 + 1);
		}
	}

	return fw_iso_resources_allocate(resources,
				amdtp_stream_get_max_payload(stream),
				fw_parent_device(dice->unit)->max_speed);
}