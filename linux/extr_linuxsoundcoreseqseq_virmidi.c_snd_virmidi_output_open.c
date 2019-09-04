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
struct snd_virmidi_dev {int /*<<< orphan*/  port; int /*<<< orphan*/  client; int /*<<< orphan*/  seq_mode; } ;
struct snd_virmidi {int /*<<< orphan*/  output_work; struct snd_virmidi_dev* rdev; int /*<<< orphan*/  event; int /*<<< orphan*/  port; int /*<<< orphan*/  client; int /*<<< orphan*/  seq_mode; int /*<<< orphan*/  parser; struct snd_rawmidi_substream* substream; } ;
struct snd_rawmidi_substream {struct snd_rawmidi_runtime* runtime; TYPE_1__* rmidi; } ;
struct snd_rawmidi_runtime {struct snd_virmidi* private_data; } ;
struct TYPE_2__ {struct snd_virmidi_dev* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_MIDI_EVENT_BUF ; 
 int /*<<< orphan*/  kfree (struct snd_virmidi*) ; 
 struct snd_virmidi* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_midi_event_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_virmidi_init_event (struct snd_virmidi*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_vmidi_output_work ; 

__attribute__((used)) static int snd_virmidi_output_open(struct snd_rawmidi_substream *substream)
{
	struct snd_virmidi_dev *rdev = substream->rmidi->private_data;
	struct snd_rawmidi_runtime *runtime = substream->runtime;
	struct snd_virmidi *vmidi;

	vmidi = kzalloc(sizeof(*vmidi), GFP_KERNEL);
	if (vmidi == NULL)
		return -ENOMEM;
	vmidi->substream = substream;
	if (snd_midi_event_new(MAX_MIDI_EVENT_BUF, &vmidi->parser) < 0) {
		kfree(vmidi);
		return -ENOMEM;
	}
	vmidi->seq_mode = rdev->seq_mode;
	vmidi->client = rdev->client;
	vmidi->port = rdev->port;
	snd_virmidi_init_event(vmidi, &vmidi->event);
	vmidi->rdev = rdev;
	INIT_WORK(&vmidi->output_work, snd_vmidi_output_work);
	runtime->private_data = vmidi;
	return 0;
}