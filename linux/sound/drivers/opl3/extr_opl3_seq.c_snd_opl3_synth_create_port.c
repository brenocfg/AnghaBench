#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_port_callback {struct snd_opl3* private_data; int /*<<< orphan*/  private_free; int /*<<< orphan*/  event_input; int /*<<< orphan*/  unuse; int /*<<< orphan*/  use; int /*<<< orphan*/  owner; } ;
struct snd_opl3 {int hardware; TYPE_1__* chset; int /*<<< orphan*/  seq_client; } ;
typedef  int /*<<< orphan*/  callbacks ;
struct TYPE_3__ {int port; int /*<<< orphan*/  client; struct snd_opl3* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAX_OPL2_VOICES ; 
 int MAX_OPL3_VOICES ; 
 int OPL3_HW_MASK ; 
 int OPL3_HW_OPL3 ; 
 int SNDRV_SEQ_PORT_CAP_SUBS_WRITE ; 
 int SNDRV_SEQ_PORT_CAP_WRITE ; 
 int SNDRV_SEQ_PORT_TYPE_DIRECT_SAMPLE ; 
 int SNDRV_SEQ_PORT_TYPE_HARDWARE ; 
 int SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC ; 
 int SNDRV_SEQ_PORT_TYPE_MIDI_GM ; 
 int SNDRV_SEQ_PORT_TYPE_SYNTHESIZER ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  memset (struct snd_seq_port_callback*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* snd_midi_channel_alloc_set (int) ; 
 int /*<<< orphan*/  snd_midi_channel_free_set (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_opl3_synth_event_input ; 
 int /*<<< orphan*/  snd_opl3_synth_free_port ; 
 int /*<<< orphan*/  snd_opl3_synth_unuse ; 
 int /*<<< orphan*/  snd_opl3_synth_use ; 
 int snd_seq_event_port_attach (int /*<<< orphan*/ ,struct snd_seq_port_callback*,int,int,int,int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int snd_opl3_synth_create_port(struct snd_opl3 * opl3)
{
	struct snd_seq_port_callback callbacks;
	char name[32];
	int voices, opl_ver;

	voices = (opl3->hardware < OPL3_HW_OPL3) ?
		MAX_OPL2_VOICES : MAX_OPL3_VOICES;
	opl3->chset = snd_midi_channel_alloc_set(16);
	if (opl3->chset == NULL)
		return -ENOMEM;
	opl3->chset->private_data = opl3;

	memset(&callbacks, 0, sizeof(callbacks));
	callbacks.owner = THIS_MODULE;
	callbacks.use = snd_opl3_synth_use;
	callbacks.unuse = snd_opl3_synth_unuse;
	callbacks.event_input = snd_opl3_synth_event_input;
	callbacks.private_free = snd_opl3_synth_free_port;
	callbacks.private_data = opl3;

	opl_ver = (opl3->hardware & OPL3_HW_MASK) >> 8;
	sprintf(name, "OPL%i FM Port", opl_ver);

	opl3->chset->client = opl3->seq_client;
	opl3->chset->port = snd_seq_event_port_attach(opl3->seq_client, &callbacks,
						      SNDRV_SEQ_PORT_CAP_WRITE |
						      SNDRV_SEQ_PORT_CAP_SUBS_WRITE,
						      SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC |
						      SNDRV_SEQ_PORT_TYPE_MIDI_GM |
						      SNDRV_SEQ_PORT_TYPE_DIRECT_SAMPLE |
						      SNDRV_SEQ_PORT_TYPE_HARDWARE |
						      SNDRV_SEQ_PORT_TYPE_SYNTHESIZER,
						      16, voices,
						      name);
	if (opl3->chset->port < 0) {
		int port;
		port = opl3->chset->port;
		snd_midi_channel_free_set(opl3->chset);
		return port;
	}
	return 0;
}