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
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct snd_pcm_audio_tstamp_report {int accuracy_report; int accuracy; scalar_t__ actual_type; } ;
struct snd_pcm_audio_tstamp_config {scalar_t__ type_requested; scalar_t__ report_delay; } ;
struct hdac_stream {int /*<<< orphan*/  tc; } ;
struct hdac_ext_stream {int dummy; } ;
struct TYPE_3__ {int info; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT ; 
 scalar_t__ SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK ; 
 int SNDRV_PCM_INFO_HAS_LINK_ATIME ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int) ; 
 struct hdac_ext_stream* get_hdac_ext_stream (struct snd_pcm_substream*) ; 
 struct hdac_stream* hdac_stream (struct hdac_ext_stream*) ; 
 struct timespec ns_to_timespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_adjust_codec_delay (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_gettime (TYPE_2__*,struct timespec*) ; 
 int /*<<< orphan*/  timecounter_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int skl_get_time_info(struct snd_pcm_substream *substream,
			struct timespec *system_ts, struct timespec *audio_ts,
			struct snd_pcm_audio_tstamp_config *audio_tstamp_config,
			struct snd_pcm_audio_tstamp_report *audio_tstamp_report)
{
	struct hdac_ext_stream *sstream = get_hdac_ext_stream(substream);
	struct hdac_stream *hstr = hdac_stream(sstream);
	u64 nsec;

	if ((substream->runtime->hw.info & SNDRV_PCM_INFO_HAS_LINK_ATIME) &&
		(audio_tstamp_config->type_requested == SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK)) {

		snd_pcm_gettime(substream->runtime, system_ts);

		nsec = timecounter_read(&hstr->tc);
		nsec = div_u64(nsec, 3); /* can be optimized */
		if (audio_tstamp_config->report_delay)
			nsec = skl_adjust_codec_delay(substream, nsec);

		*audio_ts = ns_to_timespec(nsec);

		audio_tstamp_report->actual_type = SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK;
		audio_tstamp_report->accuracy_report = 1; /* rest of struct is valid */
		audio_tstamp_report->accuracy = 42; /* 24MHzWallClk == 42ns resolution */

	} else {
		audio_tstamp_report->actual_type = SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT;
	}

	return 0;
}