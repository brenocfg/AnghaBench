#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  client; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct snd_seq_event {TYPE_2__ dest; TYPE_1__ source; } ;
struct snd_rawmidi_substream {struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {scalar_t__ avail; struct seq_midisynth* private_data; } ;
struct seq_midisynth {int /*<<< orphan*/  seq_client; int /*<<< orphan*/  seq_port; int /*<<< orphan*/ * parser; } ;
typedef  int /*<<< orphan*/  ev ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_ADDRESS_SUBSCRIBERS ; 
 int /*<<< orphan*/  memset (struct snd_seq_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_midi_event_encode_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct snd_seq_event*) ; 
 long snd_rawmidi_kernel_read (struct snd_rawmidi_substream*,char*,int) ; 
 int /*<<< orphan*/  snd_seq_kernel_client_dispatch (int /*<<< orphan*/ ,struct snd_seq_event*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_midi_input_event(struct snd_rawmidi_substream *substream)
{
	struct snd_rawmidi_runtime *runtime;
	struct seq_midisynth *msynth;
	struct snd_seq_event ev;
	char buf[16], *pbuf;
	long res;

	if (substream == NULL)
		return;
	runtime = substream->runtime;
	msynth = runtime->private_data;
	if (msynth == NULL)
		return;
	memset(&ev, 0, sizeof(ev));
	while (runtime->avail > 0) {
		res = snd_rawmidi_kernel_read(substream, buf, sizeof(buf));
		if (res <= 0)
			continue;
		if (msynth->parser == NULL)
			continue;
		pbuf = buf;
		while (res-- > 0) {
			if (!snd_midi_event_encode_byte(msynth->parser,
							*pbuf++, &ev))
				continue;
			ev.source.port = msynth->seq_port;
			ev.dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;
			snd_seq_kernel_client_dispatch(msynth->seq_client, &ev, 1, 0);
			/* clear event and reset header */
			memset(&ev, 0, sizeof(ev));
		}
	}
}