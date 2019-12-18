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
typedef  int uint32_t ;
struct rtmp_stream {int got_first_video; int max_shutdown_time_sec; long audio_bitrate; long dbr_orig_bitrate; long dbr_cur_bitrate; int dbr_inc_bitrate; int dbr_enabled; int drop_threshold_usec; int pframe_drop_threshold_usec; void* low_latency_mode; void* new_socket_loop; int /*<<< orphan*/  bind_ip; int /*<<< orphan*/  output; scalar_t__ dbr_inc_timeout; scalar_t__ dbr_est_bitrate; scalar_t__ dbr_data_size; int /*<<< orphan*/  dbr_frames; int /*<<< orphan*/  key; int /*<<< orphan*/  path; int /*<<< orphan*/  password; int /*<<< orphan*/  username; scalar_t__ min_priority; scalar_t__ dropped_frames; scalar_t__ total_bytes_sent; int /*<<< orphan*/  encode_error; int /*<<< orphan*/  disconnected; int /*<<< orphan*/  send_thread; } ;
typedef  int /*<<< orphan*/  obs_service_t ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int int64_t ;

/* Variables and functions */
 int OBS_ENCODER_CAP_DYN_BITRATE ; 
 int /*<<< orphan*/  OPT_BIND_IP ; 
 char* OPT_DROP_THRESHOLD ; 
 int /*<<< orphan*/  OPT_DYN_BITRATE ; 
 int /*<<< orphan*/  OPT_LOWLATENCY_ENABLED ; 
 char* OPT_MAX_SHUTDOWN_TIME_SEC ; 
 int /*<<< orphan*/  OPT_NEWSOCKETLOOP_ENABLED ; 
 char* OPT_PFRAME_DROP_THRESHOLD ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dstr_copy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dstr_depad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_packets (struct rtmp_stream*) ; 
 int /*<<< orphan*/  info (char*) ; 
 void* obs_data_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int obs_encoder_get_caps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_encoder_get_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_get_audio_encoder (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ obs_output_get_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ ) ; 
 char const* obs_service_get_key (int /*<<< orphan*/ *) ; 
 char const* obs_service_get_password (int /*<<< orphan*/ *) ; 
 char const* obs_service_get_url (int /*<<< orphan*/ *) ; 
 char const* obs_service_get_username (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stopping (struct rtmp_stream*) ; 

__attribute__((used)) static bool init_connect(struct rtmp_stream *stream)
{
	obs_service_t *service;
	obs_data_t *settings;
	const char *bind_ip;
	int64_t drop_p;
	int64_t drop_b;
	uint32_t caps;

	if (stopping(stream)) {
		pthread_join(stream->send_thread, NULL);
	}

	free_packets(stream);

	service = obs_output_get_service(stream->output);
	if (!service)
		return false;

	os_atomic_set_bool(&stream->disconnected, false);
	os_atomic_set_bool(&stream->encode_error, false);
	stream->total_bytes_sent = 0;
	stream->dropped_frames = 0;
	stream->min_priority = 0;
	stream->got_first_video = false;

	settings = obs_output_get_settings(stream->output);
	dstr_copy(&stream->path, obs_service_get_url(service));
	dstr_copy(&stream->key, obs_service_get_key(service));
	dstr_copy(&stream->username, obs_service_get_username(service));
	dstr_copy(&stream->password, obs_service_get_password(service));
	dstr_depad(&stream->path);
	dstr_depad(&stream->key);
	drop_b = (int64_t)obs_data_get_int(settings, OPT_DROP_THRESHOLD);
	drop_p = (int64_t)obs_data_get_int(settings, OPT_PFRAME_DROP_THRESHOLD);
	stream->max_shutdown_time_sec =
		(int)obs_data_get_int(settings, OPT_MAX_SHUTDOWN_TIME_SEC);

	obs_encoder_t *venc = obs_output_get_video_encoder(stream->output);
	obs_encoder_t *aenc = obs_output_get_audio_encoder(stream->output, 0);
	obs_data_t *vsettings = obs_encoder_get_settings(venc);
	obs_data_t *asettings = obs_encoder_get_settings(aenc);

	circlebuf_free(&stream->dbr_frames);
	stream->audio_bitrate = (long)obs_data_get_int(asettings, "bitrate");
	stream->dbr_data_size = 0;
	stream->dbr_orig_bitrate = (long)obs_data_get_int(vsettings, "bitrate");
	stream->dbr_cur_bitrate = stream->dbr_orig_bitrate;
	stream->dbr_est_bitrate = 0;
	stream->dbr_inc_bitrate = stream->dbr_orig_bitrate / 10;
	stream->dbr_inc_timeout = 0;
	stream->dbr_enabled = obs_data_get_bool(settings, OPT_DYN_BITRATE);

	caps = obs_encoder_get_caps(venc);
	if ((caps & OBS_ENCODER_CAP_DYN_BITRATE) == 0) {
		stream->dbr_enabled = false;
	}

	if (obs_output_get_delay(stream->output) != 0) {
		stream->dbr_enabled = false;
	}

	if (stream->dbr_enabled) {
		info("Dynamic bitrate enabled.  Dropped frames begone!");
	}

	obs_data_release(vsettings);
	obs_data_release(asettings);

	if (drop_p < (drop_b + 200))
		drop_p = drop_b + 200;

	stream->drop_threshold_usec = 1000 * drop_b;
	stream->pframe_drop_threshold_usec = 1000 * drop_p;

	bind_ip = obs_data_get_string(settings, OPT_BIND_IP);
	dstr_copy(&stream->bind_ip, bind_ip);

	stream->new_socket_loop =
		obs_data_get_bool(settings, OPT_NEWSOCKETLOOP_ENABLED);
	stream->low_latency_mode =
		obs_data_get_bool(settings, OPT_LOWLATENCY_ENABLED);

	obs_data_release(settings);
	return true;
}