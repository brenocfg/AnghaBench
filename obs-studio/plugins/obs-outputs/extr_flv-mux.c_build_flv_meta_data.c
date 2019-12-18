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
typedef  int /*<<< orphan*/  video_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct dstr {char* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_output_t ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMF_ECMA_ARRAY ; 
 char* AMF_EncodeInt32 (char*,char*,int) ; 
 int /*<<< orphan*/  AMF_OBJECT_END ; 
 int /*<<< orphan*/  LIBOBS_API_MAJOR_VER ; 
 int /*<<< orphan*/  LIBOBS_API_MINOR_VER ; 
 int /*<<< orphan*/  LIBOBS_API_PATCH_VER ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 char* OBS_VERSION ; 
 int audio_output_get_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bmemdup (char*,size_t) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_catf (struct dstr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enc_bool_val (char**,char*,char*,int) ; 
 int /*<<< orphan*/  enc_num_val (char**,char*,char*,double) ; 
 int /*<<< orphan*/  enc_str (char**,char*,char*) ; 
 int /*<<< orphan*/  enc_str_val (char**,char*,char*,char*) ; 
 double encoder_bitrate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_encoder_audio (int /*<<< orphan*/ *) ; 
 scalar_t__ obs_encoder_get_height (int /*<<< orphan*/ *) ; 
 scalar_t__ obs_encoder_get_sample_rate (int /*<<< orphan*/ *) ; 
 scalar_t__ obs_encoder_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_encoder_video (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_get_audio_encoder (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ *) ; 
 double video_output_get_frame_rate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool build_flv_meta_data(obs_output_t *context, uint8_t **output,
				size_t *size, size_t a_idx)
{
	obs_encoder_t *vencoder = obs_output_get_video_encoder(context);
	obs_encoder_t *aencoder = obs_output_get_audio_encoder(context, a_idx);
	video_t *video = obs_encoder_video(vencoder);
	audio_t *audio = obs_encoder_audio(aencoder);
	char buf[4096];
	char *enc = buf;
	char *end = enc + sizeof(buf);
	struct dstr encoder_name = {0};

	if (a_idx > 0 && !aencoder)
		return false;

	enc_str(&enc, end, "onMetaData");

	*enc++ = AMF_ECMA_ARRAY;
	enc = AMF_EncodeInt32(enc, end, a_idx == 0 ? 20 : 15);

	enc_num_val(&enc, end, "duration", 0.0);
	enc_num_val(&enc, end, "fileSize", 0.0);

	if (a_idx == 0) {
		enc_num_val(&enc, end, "width",
			    (double)obs_encoder_get_width(vencoder));
		enc_num_val(&enc, end, "height",
			    (double)obs_encoder_get_height(vencoder));

		enc_str_val(&enc, end, "videocodecid", "avc1");
		enc_num_val(&enc, end, "videodatarate",
			    encoder_bitrate(vencoder));
		enc_num_val(&enc, end, "framerate",
			    video_output_get_frame_rate(video));
	}

	enc_str_val(&enc, end, "audiocodecid", "mp4a");
	enc_num_val(&enc, end, "audiodatarate", encoder_bitrate(aencoder));
	enc_num_val(&enc, end, "audiosamplerate",
		    (double)obs_encoder_get_sample_rate(aencoder));
	enc_num_val(&enc, end, "audiosamplesize", 16.0);
	enc_num_val(&enc, end, "audiochannels",
		    (double)audio_output_get_channels(audio));

	enc_bool_val(&enc, end, "stereo",
		     audio_output_get_channels(audio) == 2);
	enc_bool_val(&enc, end, "2.1", audio_output_get_channels(audio) == 3);
	enc_bool_val(&enc, end, "3.1", audio_output_get_channels(audio) == 4);
	enc_bool_val(&enc, end, "4.0", audio_output_get_channels(audio) == 4);
	enc_bool_val(&enc, end, "4.1", audio_output_get_channels(audio) == 5);
	enc_bool_val(&enc, end, "5.1", audio_output_get_channels(audio) == 6);
	enc_bool_val(&enc, end, "7.1", audio_output_get_channels(audio) == 8);

	dstr_printf(&encoder_name, "%s (libobs version ", MODULE_NAME);

#ifdef HAVE_OBSCONFIG_H
	dstr_cat(&encoder_name, OBS_VERSION);
#else
	dstr_catf(&encoder_name, "%d.%d.%d", LIBOBS_API_MAJOR_VER,
		  LIBOBS_API_MINOR_VER, LIBOBS_API_PATCH_VER);
#endif

	dstr_cat(&encoder_name, ")");

	enc_str_val(&enc, end, "encoder", encoder_name.array);
	dstr_free(&encoder_name);

	*enc++ = 0;
	*enc++ = 0;
	*enc++ = AMF_OBJECT_END;

	*size = enc - buf;
	*output = bmemdup(buf, *size);
	return true;
}