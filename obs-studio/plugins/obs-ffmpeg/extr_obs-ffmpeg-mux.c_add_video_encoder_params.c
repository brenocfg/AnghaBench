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
struct video_output_info {scalar_t__ fps_den; scalar_t__ fps_num; } ;
struct ffmpeg_muxer {int /*<<< orphan*/  output; } ;
struct dstr {int dummy; } ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_catf (struct dstr*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_encoder_get_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_encoder_get_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_get_video () ; 
 int /*<<< orphan*/  obs_output_get_height (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_get_width (int /*<<< orphan*/ ) ; 
 struct video_output_info* video_output_get_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_video_encoder_params(struct ffmpeg_muxer *stream,
				     struct dstr *cmd, obs_encoder_t *vencoder)
{
	obs_data_t *settings = obs_encoder_get_settings(vencoder);
	int bitrate = (int)obs_data_get_int(settings, "bitrate");
	video_t *video = obs_get_video();
	const struct video_output_info *info = video_output_get_info(video);

	obs_data_release(settings);

	dstr_catf(cmd, "%s %d %d %d %d %d ", obs_encoder_get_codec(vencoder),
		  bitrate, obs_output_get_width(stream->output),
		  obs_output_get_height(stream->output), (int)info->fps_num,
		  (int)info->fps_den);
}