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
struct urb {int transfer_buffer_length; unsigned char* transfer_buffer; } ;
struct snd_line6_pcm {unsigned char* prev_fbuf; scalar_t__ impulse_count; unsigned char impulse_volume; scalar_t__ impulse_period; } ;

/* Variables and functions */

__attribute__((used)) static void create_impulse_test_signal(struct snd_line6_pcm *line6pcm,
				       struct urb *urb_out, int bytes_per_frame)
{
	int frames = urb_out->transfer_buffer_length / bytes_per_frame;

	if (bytes_per_frame == 4) {
		int i;
		short *pi = (short *)line6pcm->prev_fbuf;
		short *po = (short *)urb_out->transfer_buffer;

		for (i = 0; i < frames; ++i) {
			po[0] = pi[0];
			po[1] = 0;
			pi += 2;
			po += 2;
		}
	} else if (bytes_per_frame == 6) {
		int i, j;
		unsigned char *pi = line6pcm->prev_fbuf;
		unsigned char *po = urb_out->transfer_buffer;

		for (i = 0; i < frames; ++i) {
			for (j = 0; j < bytes_per_frame / 2; ++j)
				po[j] = pi[j];

			for (; j < bytes_per_frame; ++j)
				po[j] = 0;

			pi += bytes_per_frame;
			po += bytes_per_frame;
		}
	}
	if (--line6pcm->impulse_count <= 0) {
		((unsigned char *)(urb_out->transfer_buffer))[bytes_per_frame -
							      1] =
		    line6pcm->impulse_volume;
		line6pcm->impulse_count = line6pcm->impulse_period;
	}
}