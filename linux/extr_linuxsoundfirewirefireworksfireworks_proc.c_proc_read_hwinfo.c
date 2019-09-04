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
struct snd_info_entry {struct snd_efw* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_efw_hwinfo {unsigned short guid_hi; unsigned short guid_lo; unsigned short type; unsigned short version; unsigned short vendor_name; unsigned short model_name; unsigned short dsp_version; unsigned short arm_version; unsigned short fpga_version; unsigned short flags; unsigned short max_sample_rate; unsigned short min_sample_rate; unsigned short supported_clocks; unsigned short phys_out; unsigned short phys_in; unsigned short phys_in_grp_count; unsigned short phys_out_grp_count; unsigned short amdtp_rx_pcm_channels; unsigned short amdtp_tx_pcm_channels; unsigned short amdtp_rx_pcm_channels_2x; unsigned short amdtp_tx_pcm_channels_2x; unsigned short amdtp_rx_pcm_channels_4x; unsigned short amdtp_tx_pcm_channels_4x; unsigned short midi_out_ports; unsigned short midi_in_ports; unsigned short mixer_playback_channels; unsigned short mixer_capture_channels; TYPE_1__* phys_out_grps; } ;
struct snd_efw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct snd_efw_hwinfo*) ; 
 struct snd_efw_hwinfo* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_efw_command_get_hwinfo (struct snd_efw*,struct snd_efw_hwinfo*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,unsigned short,...) ; 

__attribute__((used)) static void
proc_read_hwinfo(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	struct snd_efw *efw = entry->private_data;
	unsigned short i;
	struct snd_efw_hwinfo *hwinfo;

	hwinfo = kmalloc(sizeof(struct snd_efw_hwinfo), GFP_KERNEL);
	if (hwinfo == NULL)
		return;

	if (snd_efw_command_get_hwinfo(efw, hwinfo) < 0)
		goto end;

	snd_iprintf(buffer, "guid_hi: 0x%X\n", hwinfo->guid_hi);
	snd_iprintf(buffer, "guid_lo: 0x%X\n", hwinfo->guid_lo);
	snd_iprintf(buffer, "type: 0x%X\n", hwinfo->type);
	snd_iprintf(buffer, "version: 0x%X\n", hwinfo->version);
	snd_iprintf(buffer, "vendor_name: %s\n", hwinfo->vendor_name);
	snd_iprintf(buffer, "model_name: %s\n", hwinfo->model_name);

	snd_iprintf(buffer, "dsp_version: 0x%X\n", hwinfo->dsp_version);
	snd_iprintf(buffer, "arm_version: 0x%X\n", hwinfo->arm_version);
	snd_iprintf(buffer, "fpga_version: 0x%X\n", hwinfo->fpga_version);

	snd_iprintf(buffer, "flags: 0x%X\n", hwinfo->flags);

	snd_iprintf(buffer, "max_sample_rate: 0x%X\n", hwinfo->max_sample_rate);
	snd_iprintf(buffer, "min_sample_rate: 0x%X\n", hwinfo->min_sample_rate);
	snd_iprintf(buffer, "supported_clock: 0x%X\n",
		    hwinfo->supported_clocks);

	snd_iprintf(buffer, "phys out: 0x%X\n", hwinfo->phys_out);
	snd_iprintf(buffer, "phys in: 0x%X\n", hwinfo->phys_in);

	snd_iprintf(buffer, "phys in grps: 0x%X\n",
		    hwinfo->phys_in_grp_count);
	for (i = 0; i < hwinfo->phys_in_grp_count; i++) {
		snd_iprintf(buffer,
			    "phys in grp[%d]: type 0x%X, count 0x%X\n",
			    i, hwinfo->phys_out_grps[i].type,
			    hwinfo->phys_out_grps[i].count);
	}

	snd_iprintf(buffer, "phys out grps: 0x%X\n",
		    hwinfo->phys_out_grp_count);
	for (i = 0; i < hwinfo->phys_out_grp_count; i++) {
		snd_iprintf(buffer,
			    "phys out grps[%d]: type 0x%X, count 0x%X\n",
			    i, hwinfo->phys_out_grps[i].type,
			    hwinfo->phys_out_grps[i].count);
	}

	snd_iprintf(buffer, "amdtp rx pcm channels 1x: 0x%X\n",
		    hwinfo->amdtp_rx_pcm_channels);
	snd_iprintf(buffer, "amdtp tx pcm channels 1x: 0x%X\n",
		    hwinfo->amdtp_tx_pcm_channels);
	snd_iprintf(buffer, "amdtp rx pcm channels 2x: 0x%X\n",
		    hwinfo->amdtp_rx_pcm_channels_2x);
	snd_iprintf(buffer, "amdtp tx pcm channels 2x: 0x%X\n",
		    hwinfo->amdtp_tx_pcm_channels_2x);
	snd_iprintf(buffer, "amdtp rx pcm channels 4x: 0x%X\n",
		    hwinfo->amdtp_rx_pcm_channels_4x);
	snd_iprintf(buffer, "amdtp tx pcm channels 4x: 0x%X\n",
		    hwinfo->amdtp_tx_pcm_channels_4x);

	snd_iprintf(buffer, "midi out ports: 0x%X\n", hwinfo->midi_out_ports);
	snd_iprintf(buffer, "midi in ports: 0x%X\n", hwinfo->midi_in_ports);

	snd_iprintf(buffer, "mixer playback channels: 0x%X\n",
		    hwinfo->mixer_playback_channels);
	snd_iprintf(buffer, "mixer capture channels: 0x%X\n",
		    hwinfo->mixer_capture_channels);
end:
	kfree(hwinfo);
}