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
struct hdsp {int control_register; int io_type; int system_sample_rate; scalar_t__ capture_pid; scalar_t__ playback_pid; int firmware_rev; int /*<<< orphan*/  channel_map; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  Digiface 132 
 int EBUSY ; 
 int EINVAL ; 
#define  H9632 131 
#define  H9652 130 
 scalar_t__ HDSP_AUTOSYNC_FROM_ADAT1 ; 
 int HDSP_ClockModeMaster ; 
 int HDSP_Frequency128KHz ; 
 int HDSP_Frequency176_4KHz ; 
 int HDSP_Frequency192KHz ; 
 int HDSP_Frequency32KHz ; 
 int HDSP_Frequency44_1KHz ; 
 int HDSP_Frequency48KHz ; 
 int HDSP_Frequency64KHz ; 
 int HDSP_Frequency88_2KHz ; 
 int HDSP_Frequency96KHz ; 
 int HDSP_FrequencyMask ; 
 int /*<<< orphan*/  HDSP_controlRegister ; 
#define  Multiface 129 
#define  RPM 128 
 int /*<<< orphan*/  channel_map_H9632_ds ; 
 int /*<<< orphan*/  channel_map_H9632_qs ; 
 int /*<<< orphan*/  channel_map_H9632_ss ; 
 int /*<<< orphan*/  channel_map_df_ss ; 
 int /*<<< orphan*/  channel_map_ds ; 
 int /*<<< orphan*/  channel_map_mf_ss ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ hdsp_autosync_ref (struct hdsp*) ; 
 int hdsp_external_sample_rate (struct hdsp*) ; 
 int /*<<< orphan*/  hdsp_set_dds_value (struct hdsp*,int) ; 
 int hdsp_spdif_sample_rate (struct hdsp*) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdsp_set_rate(struct hdsp *hdsp, int rate, int called_internally)
{
	int reject_if_open = 0;
	int current_rate;
	int rate_bits;

	/* ASSUMPTION: hdsp->lock is either held, or
	   there is no need for it (e.g. during module
	   initialization).
	*/

	if (!(hdsp->control_register & HDSP_ClockModeMaster)) {
		if (called_internally) {
			/* request from ctl or card initialization */
			dev_err(hdsp->card->dev,
				"device is not running as a clock master: cannot set sample rate.\n");
			return -1;
		} else {
			/* hw_param request while in AutoSync mode */
			int external_freq = hdsp_external_sample_rate(hdsp);
			int spdif_freq = hdsp_spdif_sample_rate(hdsp);

			if ((spdif_freq == external_freq*2) && (hdsp_autosync_ref(hdsp) >= HDSP_AUTOSYNC_FROM_ADAT1))
				dev_info(hdsp->card->dev,
					 "Detected ADAT in double speed mode\n");
			else if (hdsp->io_type == H9632 && (spdif_freq == external_freq*4) && (hdsp_autosync_ref(hdsp) >= HDSP_AUTOSYNC_FROM_ADAT1))
				dev_info(hdsp->card->dev,
					 "Detected ADAT in quad speed mode\n");
			else if (rate != external_freq) {
				dev_info(hdsp->card->dev,
					 "No AutoSync source for requested rate\n");
				return -1;
			}
		}
	}

	current_rate = hdsp->system_sample_rate;

	/* Changing from a "single speed" to a "double speed" rate is
	   not allowed if any substreams are open. This is because
	   such a change causes a shift in the location of
	   the DMA buffers and a reduction in the number of available
	   buffers.

	   Note that a similar but essentially insoluble problem
	   exists for externally-driven rate changes. All we can do
	   is to flag rate changes in the read/write routines.  */

	if (rate > 96000 && hdsp->io_type != H9632)
		return -EINVAL;

	switch (rate) {
	case 32000:
		if (current_rate > 48000)
			reject_if_open = 1;
		rate_bits = HDSP_Frequency32KHz;
		break;
	case 44100:
		if (current_rate > 48000)
			reject_if_open = 1;
		rate_bits = HDSP_Frequency44_1KHz;
		break;
	case 48000:
		if (current_rate > 48000)
			reject_if_open = 1;
		rate_bits = HDSP_Frequency48KHz;
		break;
	case 64000:
		if (current_rate <= 48000 || current_rate > 96000)
			reject_if_open = 1;
		rate_bits = HDSP_Frequency64KHz;
		break;
	case 88200:
		if (current_rate <= 48000 || current_rate > 96000)
			reject_if_open = 1;
		rate_bits = HDSP_Frequency88_2KHz;
		break;
	case 96000:
		if (current_rate <= 48000 || current_rate > 96000)
			reject_if_open = 1;
		rate_bits = HDSP_Frequency96KHz;
		break;
	case 128000:
		if (current_rate < 128000)
			reject_if_open = 1;
		rate_bits = HDSP_Frequency128KHz;
		break;
	case 176400:
		if (current_rate < 128000)
			reject_if_open = 1;
		rate_bits = HDSP_Frequency176_4KHz;
		break;
	case 192000:
		if (current_rate < 128000)
			reject_if_open = 1;
		rate_bits = HDSP_Frequency192KHz;
		break;
	default:
		return -EINVAL;
	}

	if (reject_if_open && (hdsp->capture_pid >= 0 || hdsp->playback_pid >= 0)) {
		dev_warn(hdsp->card->dev,
			 "cannot change speed mode (capture PID = %d, playback PID = %d)\n",
			    hdsp->capture_pid,
			    hdsp->playback_pid);
		return -EBUSY;
	}

	hdsp->control_register &= ~HDSP_FrequencyMask;
	hdsp->control_register |= rate_bits;
	hdsp_write(hdsp, HDSP_controlRegister, hdsp->control_register);

	/* For HDSP9632 rev 152, need to set DDS value in FREQ register */
	if (hdsp->io_type == H9632 && hdsp->firmware_rev >= 152)
		hdsp_set_dds_value(hdsp, rate);

	if (rate >= 128000) {
		hdsp->channel_map = channel_map_H9632_qs;
	} else if (rate > 48000) {
		if (hdsp->io_type == H9632)
			hdsp->channel_map = channel_map_H9632_ds;
		else
			hdsp->channel_map = channel_map_ds;
	} else {
		switch (hdsp->io_type) {
		case RPM:
		case Multiface:
			hdsp->channel_map = channel_map_mf_ss;
			break;
		case Digiface:
		case H9652:
			hdsp->channel_map = channel_map_df_ss;
			break;
		case H9632:
			hdsp->channel_map = channel_map_H9632_ss;
			break;
		default:
			/* should never happen */
			break;
		}
	}

	hdsp->system_sample_rate = rate;

	return 0;
}