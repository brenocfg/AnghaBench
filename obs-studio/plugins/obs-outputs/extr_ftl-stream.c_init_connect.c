#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  array; } ;
struct TYPE_4__ {char* stream_key; char* vendor_name; scalar_t__ peak_kbps; scalar_t__ fps_den; scalar_t__ fps_num; int /*<<< orphan*/  vendor_version; int /*<<< orphan*/  ingest_hostname; int /*<<< orphan*/  audio_codec; int /*<<< orphan*/  video_codec; } ;
struct ftl_stream {scalar_t__ peak_kbps; int drop_threshold_usec; int max_shutdown_time_sec; TYPE_2__ bind_ip; TYPE_2__ path; TYPE_2__ password; TYPE_2__ username; TYPE_1__ params; int /*<<< orphan*/  ftl_handle; int /*<<< orphan*/  output; scalar_t__ min_priority; scalar_t__ dropped_frames; scalar_t__ total_bytes_sent; int /*<<< orphan*/  encode_error; int /*<<< orphan*/  disconnected; int /*<<< orphan*/  send_thread; } ;
typedef  int /*<<< orphan*/  obs_service_t ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int int64_t ;
typedef  scalar_t__ ftl_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTL_AUDIO_OPUS ; 
 scalar_t__ FTL_BAD_OR_INVALID_STREAM_KEY ; 
 scalar_t__ FTL_SUCCESS ; 
 int /*<<< orphan*/  FTL_VIDEO_H264 ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int OBS_OUTPUT_ERROR ; 
 int OBS_OUTPUT_INVALID_STREAM ; 
 int OBS_OUTPUT_SUCCESS ; 
 int /*<<< orphan*/  OBS_VERSION ; 
 int /*<<< orphan*/  OPT_BIND_IP ; 
 char* OPT_DROP_THRESHOLD ; 
 char* OPT_MAX_SHUTDOWN_TIME_SEC ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_copy (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  dstr_depad (TYPE_2__*) ; 
 int /*<<< orphan*/  free_packets (struct ftl_stream*) ; 
 scalar_t__ ftl_ingest_create (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ftl_status_code_to_string (scalar_t__) ; 
 int /*<<< orphan*/  info (char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_encoder_get_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_get_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ ) ; 
 char* obs_service_get_key (int /*<<< orphan*/ *) ; 
 char const* obs_service_get_password (int /*<<< orphan*/ *) ; 
 char const* obs_service_get_url (int /*<<< orphan*/ *) ; 
 char const* obs_service_get_username (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stopping (struct ftl_stream*) ; 

__attribute__((used)) static int init_connect(struct ftl_stream *stream)
{
	obs_service_t *service;
	obs_data_t *settings;
	const char *bind_ip, *key;
	ftl_status_t status_code;

	info("init_connect");

	if (stopping(stream))
		pthread_join(stream->send_thread, NULL);

	free_packets(stream);

	service = obs_output_get_service(stream->output);
	if (!service) {
		return OBS_OUTPUT_ERROR;
	}

	os_atomic_set_bool(&stream->disconnected, false);
	os_atomic_set_bool(&stream->encode_error, false);
	stream->total_bytes_sent = 0;
	stream->dropped_frames = 0;
	stream->min_priority = 0;

	settings = obs_output_get_settings(stream->output);
	obs_encoder_t *video_encoder =
		obs_output_get_video_encoder(stream->output);
	obs_data_t *video_settings = obs_encoder_get_settings(video_encoder);

	dstr_copy(&stream->path, obs_service_get_url(service));
	key = obs_service_get_key(service);

	int target_bitrate = (int)obs_data_get_int(video_settings, "bitrate");
	int peak_bitrate = (int)((float)target_bitrate * 1.1f);

	//minimum overshoot tolerance of 10%
	if (peak_bitrate < target_bitrate) {
		peak_bitrate = target_bitrate;
	}

	stream->params.stream_key = (char *)key;
	stream->params.video_codec = FTL_VIDEO_H264;
	stream->params.audio_codec = FTL_AUDIO_OPUS;
	stream->params.ingest_hostname = stream->path.array;
	stream->params.vendor_name = "OBS Studio";
	stream->params.vendor_version = OBS_VERSION;
	stream->params.peak_kbps = stream->peak_kbps < 0 ? 0
							 : stream->peak_kbps;

	//not required when using ftl_ingest_send_media_dts
	stream->params.fps_num = 0;
	stream->params.fps_den = 0;

	status_code = ftl_ingest_create(&stream->ftl_handle, &stream->params);
	if (status_code != FTL_SUCCESS) {
		if (status_code == FTL_BAD_OR_INVALID_STREAM_KEY) {
			blog(LOG_ERROR, "Invalid Key (%s)",
			     ftl_status_code_to_string(status_code));
			return OBS_OUTPUT_INVALID_STREAM;
		} else {
			blog(LOG_ERROR, "Failed to create ingest handle (%s)",
			     ftl_status_code_to_string(status_code));
			return OBS_OUTPUT_ERROR;
		}
	}

	dstr_copy(&stream->username, obs_service_get_username(service));
	dstr_copy(&stream->password, obs_service_get_password(service));
	dstr_depad(&stream->path);

	stream->drop_threshold_usec =
		(int64_t)obs_data_get_int(settings, OPT_DROP_THRESHOLD) * 1000;
	stream->max_shutdown_time_sec =
		(int)obs_data_get_int(settings, OPT_MAX_SHUTDOWN_TIME_SEC);

	bind_ip = obs_data_get_string(settings, OPT_BIND_IP);
	dstr_copy(&stream->bind_ip, bind_ip);

	obs_data_release(settings);
	obs_data_release(video_settings);
	return OBS_OUTPUT_SUCCESS;
}