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
typedef  int /*<<< orphan*/  u64 ;
struct timespec {int dummy; } ;
struct system_device_crosststamp {int /*<<< orphan*/  device; int /*<<< orphan*/  sys_realtime; int /*<<< orphan*/  sys_monoraw; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {int info; } ;
struct snd_pcm_runtime {int tstamp_type; TYPE_1__ hw; } ;
struct snd_pcm_audio_tstamp_report {int accuracy_report; int accuracy; scalar_t__ actual_type; } ;
struct snd_pcm_audio_tstamp_config {scalar_t__ type_requested; scalar_t__ report_delay; } ;
struct TYPE_4__ {int /*<<< orphan*/  tc; } ;
struct azx_dev {TYPE_2__ core; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT ; 
 scalar_t__ SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK ; 
 scalar_t__ SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED ; 
 int SNDRV_PCM_INFO_HAS_LINK_ATIME ; 
#define  SNDRV_PCM_TSTAMP_TYPE_MONOTONIC 129 
#define  SNDRV_PCM_TSTAMP_TYPE_MONOTONIC_RAW 128 
 int /*<<< orphan*/  azx_adjust_codec_delay (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int azx_get_crosststamp (struct snd_pcm_substream*,struct system_device_crosststamp*) ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int) ; 
 struct azx_dev* get_azx_dev (struct snd_pcm_substream*) ; 
 scalar_t__ is_link_time_supported (struct snd_pcm_runtime*,struct snd_pcm_audio_tstamp_config*) ; 
 struct timespec ktime_to_timespec (int /*<<< orphan*/ ) ; 
 struct timespec ns_to_timespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_gettime (struct snd_pcm_runtime*,struct timespec*) ; 
 int /*<<< orphan*/  timecounter_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int azx_get_time_info(struct snd_pcm_substream *substream,
			struct timespec *system_ts, struct timespec *audio_ts,
			struct snd_pcm_audio_tstamp_config *audio_tstamp_config,
			struct snd_pcm_audio_tstamp_report *audio_tstamp_report)
{
	struct azx_dev *azx_dev = get_azx_dev(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct system_device_crosststamp xtstamp;
	int ret;
	u64 nsec;

	if ((substream->runtime->hw.info & SNDRV_PCM_INFO_HAS_LINK_ATIME) &&
		(audio_tstamp_config->type_requested == SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK)) {

		snd_pcm_gettime(substream->runtime, system_ts);

		nsec = timecounter_read(&azx_dev->core.tc);
		nsec = div_u64(nsec, 3); /* can be optimized */
		if (audio_tstamp_config->report_delay)
			nsec = azx_adjust_codec_delay(substream, nsec);

		*audio_ts = ns_to_timespec(nsec);

		audio_tstamp_report->actual_type = SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK;
		audio_tstamp_report->accuracy_report = 1; /* rest of structure is valid */
		audio_tstamp_report->accuracy = 42; /* 24 MHz WallClock == 42ns resolution */

	} else if (is_link_time_supported(runtime, audio_tstamp_config)) {

		ret = azx_get_crosststamp(substream, &xtstamp);
		if (ret)
			return ret;

		switch (runtime->tstamp_type) {
		case SNDRV_PCM_TSTAMP_TYPE_MONOTONIC:
			return -EINVAL;

		case SNDRV_PCM_TSTAMP_TYPE_MONOTONIC_RAW:
			*system_ts = ktime_to_timespec(xtstamp.sys_monoraw);
			break;

		default:
			*system_ts = ktime_to_timespec(xtstamp.sys_realtime);
			break;

		}

		*audio_ts = ktime_to_timespec(xtstamp.device);

		audio_tstamp_report->actual_type =
			SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED;
		audio_tstamp_report->accuracy_report = 1;
		/* 24 MHz WallClock == 42ns resolution */
		audio_tstamp_report->accuracy = 42;

	} else {
		audio_tstamp_report->actual_type = SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT;
	}

	return 0;
}