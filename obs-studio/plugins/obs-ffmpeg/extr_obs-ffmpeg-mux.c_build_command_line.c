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
struct ffmpeg_muxer {int /*<<< orphan*/  path; int /*<<< orphan*/  output; } ;
struct dstr {int dummy; } ;
typedef  int /*<<< orphan*/  obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  FFMPEG_MUX ; 
 int MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  add_audio_encoder_params (struct dstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_muxer_params (struct dstr*,struct ffmpeg_muxer*) ; 
 int /*<<< orphan*/  add_video_encoder_params (struct ffmpeg_muxer*,struct dstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dstr_catf (struct dstr*,char*,int,int) ; 
 int /*<<< orphan*/  dstr_copy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dstr_init_move_array (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_insert_ch (struct dstr*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  dstr_replace (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * obs_output_get_audio_encoder (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_get_executable_path_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_command_line(struct ffmpeg_muxer *stream, struct dstr *cmd,
			       const char *path)
{
	obs_encoder_t *vencoder = obs_output_get_video_encoder(stream->output);
	obs_encoder_t *aencoders[MAX_AUDIO_MIXES];
	int num_tracks = 0;

	for (;;) {
		obs_encoder_t *aencoder = obs_output_get_audio_encoder(
			stream->output, num_tracks);
		if (!aencoder)
			break;

		aencoders[num_tracks] = aencoder;
		num_tracks++;
	}

	dstr_init_move_array(cmd, os_get_executable_path_ptr(FFMPEG_MUX));
	dstr_insert_ch(cmd, 0, '\"');
	dstr_cat(cmd, "\" \"");

	dstr_copy(&stream->path, path);
	dstr_replace(&stream->path, "\"", "\"\"");
	dstr_cat_dstr(cmd, &stream->path);

	dstr_catf(cmd, "\" %d %d ", vencoder ? 1 : 0, num_tracks);

	if (vencoder)
		add_video_encoder_params(stream, cmd, vencoder);

	if (num_tracks) {
		dstr_cat(cmd, "aac ");

		for (int i = 0; i < num_tracks; i++) {
			add_audio_encoder_params(cmd, aencoders[i]);
		}
	}

	add_muxer_params(cmd, stream);
}