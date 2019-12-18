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
struct snd_line6_pcm {int max_packet_size_out; int max_packet_size_in; TYPE_1__* line6; } ;
struct line6_pcm_stream {scalar_t__ buffer; int /*<<< orphan*/  opened; } ;
struct TYPE_2__ {int /*<<< orphan*/  iso_buffers; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LINE6_ISO_PACKETS ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  array3_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int line6_buffer_acquire(struct snd_line6_pcm *line6pcm,
				struct line6_pcm_stream *pstr, int direction, int type)
{
	const int pkt_size =
		(direction == SNDRV_PCM_STREAM_PLAYBACK) ?
			line6pcm->max_packet_size_out :
			line6pcm->max_packet_size_in;

	/* Invoked multiple times in a row so allocate once only */
	if (!test_and_set_bit(type, &pstr->opened) && !pstr->buffer) {
		pstr->buffer =
			kmalloc(array3_size(line6pcm->line6->iso_buffers,
					    LINE6_ISO_PACKETS, pkt_size),
				GFP_KERNEL);
		if (!pstr->buffer)
			return -ENOMEM;
	}
	return 0;
}