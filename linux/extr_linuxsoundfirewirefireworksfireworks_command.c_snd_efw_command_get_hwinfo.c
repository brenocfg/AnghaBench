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
struct snd_efw_hwinfo {char* vendor_name; char* model_name; int /*<<< orphan*/  amdtp_tx_pcm_channels_4x; int /*<<< orphan*/  amdtp_rx_pcm_channels_4x; int /*<<< orphan*/  amdtp_tx_pcm_channels_2x; int /*<<< orphan*/  amdtp_rx_pcm_channels_2x; int /*<<< orphan*/  fpga_version; int /*<<< orphan*/  mixer_capture_channels; int /*<<< orphan*/  mixer_playback_channels; int /*<<< orphan*/  arm_version; int /*<<< orphan*/  dsp_version; int /*<<< orphan*/  min_sample_rate; int /*<<< orphan*/  max_sample_rate; int /*<<< orphan*/  midi_in_ports; int /*<<< orphan*/  midi_out_ports; int /*<<< orphan*/  phys_in_grp_count; int /*<<< orphan*/  phys_out_grp_count; int /*<<< orphan*/  phys_in; int /*<<< orphan*/  phys_out; int /*<<< orphan*/  amdtp_tx_pcm_channels; int /*<<< orphan*/  amdtp_rx_pcm_channels; int /*<<< orphan*/  supported_clocks; int /*<<< orphan*/  version; int /*<<< orphan*/  type; int /*<<< orphan*/  guid_lo; int /*<<< orphan*/  guid_hi; int /*<<< orphan*/  flags; } ;
struct snd_efw {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EFC_CAT_HWINFO ; 
 int /*<<< orphan*/  EFC_CMD_HWINFO_GET_CAPS ; 
 int HWINFO_NAME_SIZE_BYTES ; 
 int /*<<< orphan*/  be32_to_cpus (int /*<<< orphan*/ *) ; 
 int efw_transaction (struct snd_efw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int snd_efw_command_get_hwinfo(struct snd_efw *efw,
			       struct snd_efw_hwinfo *hwinfo)
{
	int err;

	err  = efw_transaction(efw, EFC_CAT_HWINFO,
			       EFC_CMD_HWINFO_GET_CAPS,
			       NULL, 0, (__be32 *)hwinfo, sizeof(*hwinfo));
	if (err < 0)
		goto end;

	be32_to_cpus(&hwinfo->flags);
	be32_to_cpus(&hwinfo->guid_hi);
	be32_to_cpus(&hwinfo->guid_lo);
	be32_to_cpus(&hwinfo->type);
	be32_to_cpus(&hwinfo->version);
	be32_to_cpus(&hwinfo->supported_clocks);
	be32_to_cpus(&hwinfo->amdtp_rx_pcm_channels);
	be32_to_cpus(&hwinfo->amdtp_tx_pcm_channels);
	be32_to_cpus(&hwinfo->phys_out);
	be32_to_cpus(&hwinfo->phys_in);
	be32_to_cpus(&hwinfo->phys_out_grp_count);
	be32_to_cpus(&hwinfo->phys_in_grp_count);
	be32_to_cpus(&hwinfo->midi_out_ports);
	be32_to_cpus(&hwinfo->midi_in_ports);
	be32_to_cpus(&hwinfo->max_sample_rate);
	be32_to_cpus(&hwinfo->min_sample_rate);
	be32_to_cpus(&hwinfo->dsp_version);
	be32_to_cpus(&hwinfo->arm_version);
	be32_to_cpus(&hwinfo->mixer_playback_channels);
	be32_to_cpus(&hwinfo->mixer_capture_channels);
	be32_to_cpus(&hwinfo->fpga_version);
	be32_to_cpus(&hwinfo->amdtp_rx_pcm_channels_2x);
	be32_to_cpus(&hwinfo->amdtp_tx_pcm_channels_2x);
	be32_to_cpus(&hwinfo->amdtp_rx_pcm_channels_4x);
	be32_to_cpus(&hwinfo->amdtp_tx_pcm_channels_4x);

	/* ensure terminated */
	hwinfo->vendor_name[HWINFO_NAME_SIZE_BYTES - 1] = '\0';
	hwinfo->model_name[HWINFO_NAME_SIZE_BYTES  - 1] = '\0';
end:
	return err;
}