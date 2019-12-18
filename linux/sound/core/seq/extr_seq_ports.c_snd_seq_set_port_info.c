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
struct snd_seq_port_info {int flags; int /*<<< orphan*/  time_queue; int /*<<< orphan*/  synth_voices; int /*<<< orphan*/  midi_voices; int /*<<< orphan*/  midi_channels; int /*<<< orphan*/  type; int /*<<< orphan*/  capability; scalar_t__* name; } ;
struct snd_seq_client_port {int timestamping; int time_real; int /*<<< orphan*/  time_queue; int /*<<< orphan*/  synth_voices; int /*<<< orphan*/  midi_voices; int /*<<< orphan*/  midi_channels; int /*<<< orphan*/  type; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_SEQ_PORT_FLG_TIMESTAMP ; 
 int SNDRV_SEQ_PORT_FLG_TIME_REAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 

int snd_seq_set_port_info(struct snd_seq_client_port * port,
			  struct snd_seq_port_info * info)
{
	if (snd_BUG_ON(!port || !info))
		return -EINVAL;

	/* set port name */
	if (info->name[0])
		strlcpy(port->name, info->name, sizeof(port->name));
	
	/* set capabilities */
	port->capability = info->capability;
	
	/* get port type */
	port->type = info->type;

	/* information about supported channels/voices */
	port->midi_channels = info->midi_channels;
	port->midi_voices = info->midi_voices;
	port->synth_voices = info->synth_voices;

	/* timestamping */
	port->timestamping = (info->flags & SNDRV_SEQ_PORT_FLG_TIMESTAMP) ? 1 : 0;
	port->time_real = (info->flags & SNDRV_SEQ_PORT_FLG_TIME_REAL) ? 1 : 0;
	port->time_queue = info->time_queue;

	return 0;
}