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
struct snd_seq_port_callback {struct snd_emux_port* private_data; int /*<<< orphan*/  private_free; } ;
struct TYPE_3__ {int max_channels; int /*<<< orphan*/  port; int /*<<< orphan*/  client; struct snd_emux_port* private_data; TYPE_2__* channels; } ;
struct snd_emux_port {TYPE_1__ chset; struct snd_emux* emu; } ;
struct snd_emux {int /*<<< orphan*/  max_voices; int /*<<< orphan*/  client; } ;
struct TYPE_4__ {int number; } ;

/* Variables and functions */
 int DEFAULT_MIDI_TYPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_SEQ_PORT_CAP_SUBS_WRITE ; 
 int SNDRV_SEQ_PORT_CAP_WRITE ; 
 int SNDRV_SEQ_PORT_TYPE_SPECIFIC ; 
 int /*<<< orphan*/  free_port ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_emux_port*) ; 
 struct snd_emux_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emux_create_effect (struct snd_emux_port*) ; 
 int /*<<< orphan*/  snd_seq_event_port_attach (int /*<<< orphan*/ ,struct snd_seq_port_callback*,int,int,int,int /*<<< orphan*/ ,char*) ; 

struct snd_emux_port *
snd_emux_create_port(struct snd_emux *emu, char *name,
		     int max_channels, int oss_port,
		     struct snd_seq_port_callback *callback)
{
	struct snd_emux_port *p;
	int i, type, cap;

	/* Allocate structures for this channel */
	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return NULL;

	p->chset.channels = kcalloc(max_channels, sizeof(*p->chset.channels),
				    GFP_KERNEL);
	if (!p->chset.channels) {
		kfree(p);
		return NULL;
	}
	for (i = 0; i < max_channels; i++)
		p->chset.channels[i].number = i;
	p->chset.private_data = p;
	p->chset.max_channels = max_channels;
	p->emu = emu;
	p->chset.client = emu->client;
#ifdef SNDRV_EMUX_USE_RAW_EFFECT
	snd_emux_create_effect(p);
#endif
	callback->private_free = free_port;
	callback->private_data = p;

	cap = SNDRV_SEQ_PORT_CAP_WRITE;
	if (oss_port) {
		type = SNDRV_SEQ_PORT_TYPE_SPECIFIC;
	} else {
		type = DEFAULT_MIDI_TYPE;
		cap |= SNDRV_SEQ_PORT_CAP_SUBS_WRITE;
	}

	p->chset.port = snd_seq_event_port_attach(emu->client, callback,
						  cap, type, max_channels,
						  emu->max_voices, name);

	return p;
}