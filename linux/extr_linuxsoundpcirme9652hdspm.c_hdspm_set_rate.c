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
struct hdspm {int control_register; int system_sample_rate; scalar_t__ capture_pid; scalar_t__ playback_pid; scalar_t__ io_type; int /*<<< orphan*/  port_names_out_qs; int /*<<< orphan*/  port_names_out; int /*<<< orphan*/  port_names_in_qs; int /*<<< orphan*/  port_names_in; int /*<<< orphan*/  qs_out_channels; int /*<<< orphan*/  max_channels_out; int /*<<< orphan*/  qs_in_channels; int /*<<< orphan*/  max_channels_in; int /*<<< orphan*/  channel_map_out_qs; int /*<<< orphan*/  channel_map_out; int /*<<< orphan*/  channel_map_in_qs; int /*<<< orphan*/  channel_map_in; int /*<<< orphan*/  port_names_out_ds; int /*<<< orphan*/  port_names_in_ds; int /*<<< orphan*/  ds_out_channels; int /*<<< orphan*/  ds_in_channels; int /*<<< orphan*/  channel_map_out_ds; int /*<<< orphan*/  channel_map_in_ds; int /*<<< orphan*/  port_names_out_ss; int /*<<< orphan*/  port_names_in_ss; int /*<<< orphan*/  ss_out_channels; int /*<<< orphan*/  ss_in_channels; int /*<<< orphan*/  channel_map_out_ss; int /*<<< orphan*/  channel_map_in_ss; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AES32 ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ HDSPM_AUTOSYNC_FROM_NONE ; 
 int HDSPM_ClockModeMaster ; 
 int HDSPM_Frequency128KHz ; 
 int HDSPM_Frequency176_4KHz ; 
 int HDSPM_Frequency192KHz ; 
 int HDSPM_Frequency32KHz ; 
 int HDSPM_Frequency44_1KHz ; 
 int HDSPM_Frequency48KHz ; 
 int HDSPM_Frequency64KHz ; 
 int HDSPM_Frequency88_2KHz ; 
 int HDSPM_Frequency96KHz ; 
 int HDSPM_FrequencyMask ; 
 int HDSPM_SPEED_DOUBLE ; 
 int HDSPM_SPEED_QUAD ; 
 int HDSPM_SPEED_SINGLE ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 int /*<<< orphan*/  HDSPM_eeprom_wr ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hdspm_autosync_ref (struct hdspm*) ; 
 int hdspm_external_sample_rate (struct hdspm*) ; 
 int /*<<< orphan*/  hdspm_set_dds_value (struct hdspm*,int) ; 
 int /*<<< orphan*/ * hdspm_speed_names ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdspm_set_rate(struct hdspm * hdspm, int rate, int called_internally)
{
	int current_rate;
	int rate_bits;
	int not_set = 0;
	int current_speed, target_speed;

	/* ASSUMPTION: hdspm->lock is either set, or there is no need for
	   it (e.g. during module initialization).
	 */

	if (!(hdspm->control_register & HDSPM_ClockModeMaster)) {

		/* SLAVE --- */
		if (called_internally) {

			/* request from ctl or card initialization
			   just make a warning an remember setting
			   for future master mode switching */

			dev_warn(hdspm->card->dev,
				 "Warning: device is not running as a clock master.\n");
			not_set = 1;
		} else {

			/* hw_param request while in AutoSync mode */
			int external_freq =
			    hdspm_external_sample_rate(hdspm);

			if (hdspm_autosync_ref(hdspm) ==
			    HDSPM_AUTOSYNC_FROM_NONE) {

				dev_warn(hdspm->card->dev,
					 "Detected no External Sync\n");
				not_set = 1;

			} else if (rate != external_freq) {

				dev_warn(hdspm->card->dev,
					 "Warning: No AutoSync source for requested rate\n");
				not_set = 1;
			}
		}
	}

	current_rate = hdspm->system_sample_rate;

	/* Changing between Singe, Double and Quad speed is not
	   allowed if any substreams are open. This is because such a change
	   causes a shift in the location of the DMA buffers and a reduction
	   in the number of available buffers.

	   Note that a similar but essentially insoluble problem exists for
	   externally-driven rate changes. All we can do is to flag rate
	   changes in the read/write routines.
	 */

	if (current_rate <= 48000)
		current_speed = HDSPM_SPEED_SINGLE;
	else if (current_rate <= 96000)
		current_speed = HDSPM_SPEED_DOUBLE;
	else
		current_speed = HDSPM_SPEED_QUAD;

	if (rate <= 48000)
		target_speed = HDSPM_SPEED_SINGLE;
	else if (rate <= 96000)
		target_speed = HDSPM_SPEED_DOUBLE;
	else
		target_speed = HDSPM_SPEED_QUAD;

	switch (rate) {
	case 32000:
		rate_bits = HDSPM_Frequency32KHz;
		break;
	case 44100:
		rate_bits = HDSPM_Frequency44_1KHz;
		break;
	case 48000:
		rate_bits = HDSPM_Frequency48KHz;
		break;
	case 64000:
		rate_bits = HDSPM_Frequency64KHz;
		break;
	case 88200:
		rate_bits = HDSPM_Frequency88_2KHz;
		break;
	case 96000:
		rate_bits = HDSPM_Frequency96KHz;
		break;
	case 128000:
		rate_bits = HDSPM_Frequency128KHz;
		break;
	case 176400:
		rate_bits = HDSPM_Frequency176_4KHz;
		break;
	case 192000:
		rate_bits = HDSPM_Frequency192KHz;
		break;
	default:
		return -EINVAL;
	}

	if (current_speed != target_speed
	    && (hdspm->capture_pid >= 0 || hdspm->playback_pid >= 0)) {
		dev_err(hdspm->card->dev,
			"cannot change from %s speed to %s speed mode (capture PID = %d, playback PID = %d)\n",
			hdspm_speed_names[current_speed],
			hdspm_speed_names[target_speed],
			hdspm->capture_pid, hdspm->playback_pid);
		return -EBUSY;
	}

	hdspm->control_register &= ~HDSPM_FrequencyMask;
	hdspm->control_register |= rate_bits;
	hdspm_write(hdspm, HDSPM_controlRegister, hdspm->control_register);

	/* For AES32, need to set DDS value in FREQ register
	   For MADI, also apparently */
	hdspm_set_dds_value(hdspm, rate);

	if (AES32 == hdspm->io_type && rate != current_rate)
		hdspm_write(hdspm, HDSPM_eeprom_wr, 0);

	hdspm->system_sample_rate = rate;

	if (rate <= 48000) {
		hdspm->channel_map_in = hdspm->channel_map_in_ss;
		hdspm->channel_map_out = hdspm->channel_map_out_ss;
		hdspm->max_channels_in = hdspm->ss_in_channels;
		hdspm->max_channels_out = hdspm->ss_out_channels;
		hdspm->port_names_in = hdspm->port_names_in_ss;
		hdspm->port_names_out = hdspm->port_names_out_ss;
	} else if (rate <= 96000) {
		hdspm->channel_map_in = hdspm->channel_map_in_ds;
		hdspm->channel_map_out = hdspm->channel_map_out_ds;
		hdspm->max_channels_in = hdspm->ds_in_channels;
		hdspm->max_channels_out = hdspm->ds_out_channels;
		hdspm->port_names_in = hdspm->port_names_in_ds;
		hdspm->port_names_out = hdspm->port_names_out_ds;
	} else {
		hdspm->channel_map_in = hdspm->channel_map_in_qs;
		hdspm->channel_map_out = hdspm->channel_map_out_qs;
		hdspm->max_channels_in = hdspm->qs_in_channels;
		hdspm->max_channels_out = hdspm->qs_out_channels;
		hdspm->port_names_in = hdspm->port_names_in_qs;
		hdspm->port_names_out = hdspm->port_names_out_qs;
	}

	if (not_set != 0)
		return -1;

	return 0;
}