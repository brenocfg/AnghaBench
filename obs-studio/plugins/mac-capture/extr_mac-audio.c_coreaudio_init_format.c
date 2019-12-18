#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct obs_audio_info {int /*<<< orphan*/  speakers; } ;
struct coreaudio_data {int /*<<< orphan*/  speakers; scalar_t__ sample_rate; int /*<<< orphan*/  format; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  desc ;
typedef  int UInt32 ;
struct TYPE_4__ {int mChannelsPerFrame; int mBytesPerFrame; int mBitsPerChannel; int mBytesPerPacket; int mFramesPerPacket; scalar_t__ mFormatID; scalar_t__ mSampleRate; scalar_t__ mFormatFlags; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  TYPE_1__ AudioStreamBasicDescription ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  BUS_INPUT ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  SCOPE_INPUT ; 
 int /*<<< orphan*/  SCOPE_OUTPUT ; 
 int /*<<< orphan*/  SPEAKERS_UNKNOWN ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ca_success (int /*<<< orphan*/ ,struct coreaudio_data*,char*,char*) ; 
 int /*<<< orphan*/  ca_warn (struct coreaudio_data*,char*,char*,...) ; 
 int /*<<< orphan*/  convert_ca_format (scalar_t__,int) ; 
 int /*<<< orphan*/  convert_ca_speaker_layout (int) ; 
 int get_audio_channels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 scalar_t__ kAudioFormatLinearPCM ; 
 int /*<<< orphan*/  kAudioUnitProperty_StreamFormat ; 
 int /*<<< orphan*/  obs_get_audio_info (struct obs_audio_info*) ; 
 int /*<<< orphan*/  set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static bool coreaudio_init_format(struct coreaudio_data *ca)
{
	AudioStreamBasicDescription desc;
	OSStatus stat;
	UInt32 size = sizeof(desc);
	struct obs_audio_info aoi;
	int channels;

	if (!obs_get_audio_info(&aoi)) {
		blog(LOG_WARNING, "No active audio");
		return false;
	}
	channels = get_audio_channels(aoi.speakers);

	stat = get_property(ca->unit, kAudioUnitProperty_StreamFormat,
			    SCOPE_INPUT, BUS_INPUT, &desc, &size);
	if (!ca_success(stat, ca, "coreaudio_init_format", "get input format"))
		return false;

	/* Certain types of devices have no limit on channel count, and
	 * there's no way to know the actual number of channels it's using,
	 * so if we encounter this situation just force to what is defined in output */
	if (desc.mChannelsPerFrame > 8) {
		desc.mChannelsPerFrame = channels;
		desc.mBytesPerFrame = channels * desc.mBitsPerChannel / 8;
		desc.mBytesPerPacket =
			desc.mFramesPerPacket * desc.mBytesPerFrame;
	}

	stat = set_property(ca->unit, kAudioUnitProperty_StreamFormat,
			    SCOPE_OUTPUT, BUS_INPUT, &desc, size);
	if (!ca_success(stat, ca, "coreaudio_init_format", "set output format"))
		return false;

	if (desc.mFormatID != kAudioFormatLinearPCM) {
		ca_warn(ca, "coreaudio_init_format", "format is not PCM");
		return false;
	}

	ca->format = convert_ca_format(desc.mFormatFlags, desc.mBitsPerChannel);
	if (ca->format == AUDIO_FORMAT_UNKNOWN) {
		ca_warn(ca, "coreaudio_init_format",
			"unknown format flags: "
			"%u, bits: %u",
			(unsigned int)desc.mFormatFlags,
			(unsigned int)desc.mBitsPerChannel);
		return false;
	}

	ca->sample_rate = (uint32_t)desc.mSampleRate;
	ca->speakers = convert_ca_speaker_layout(desc.mChannelsPerFrame);

	if (ca->speakers == SPEAKERS_UNKNOWN) {
		ca_warn(ca, "coreaudio_init_format",
			"unknown speaker layout: "
			"%u channels",
			(unsigned int)desc.mChannelsPerFrame);
		return false;
	}

	return true;
}