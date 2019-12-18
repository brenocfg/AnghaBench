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
struct main_params {int has_video; int tracks; int vbitrate; int width; int height; int fps_num; int fps_den; int /*<<< orphan*/  muxer_settings; int /*<<< orphan*/  acodec; int /*<<< orphan*/  vcodec; int /*<<< orphan*/  file; } ;
struct audio_params {int dummy; } ;

/* Variables and functions */
 struct audio_params* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct audio_params*) ; 
 int /*<<< orphan*/  get_audio_params (struct audio_params*,int*,char***) ; 
 int /*<<< orphan*/  get_opt_int (int*,char***,int*,char*) ; 
 int /*<<< orphan*/  get_opt_str (int*,char***,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static bool init_params(int *argc, char ***argv, struct main_params *params,
			struct audio_params **p_audio)
{
	struct audio_params *audio = NULL;

	if (!get_opt_str(argc, argv, &params->file, "file name"))
		return false;
	if (!get_opt_int(argc, argv, &params->has_video, "video track count"))
		return false;
	if (!get_opt_int(argc, argv, &params->tracks, "audio track count"))
		return false;

	if (params->has_video > 1 || params->has_video < 0) {
		puts("Invalid number of video tracks\n");
		return false;
	}
	if (params->tracks < 0) {
		puts("Invalid number of audio tracks\n");
		return false;
	}
	if (params->has_video == 0 && params->tracks == 0) {
		puts("Must have at least 1 audio track or 1 video track\n");
		return false;
	}

	if (params->has_video) {
		if (!get_opt_str(argc, argv, &params->vcodec, "video codec"))
			return false;
		if (!get_opt_int(argc, argv, &params->vbitrate,
				 "video bitrate"))
			return false;
		if (!get_opt_int(argc, argv, &params->width, "video width"))
			return false;
		if (!get_opt_int(argc, argv, &params->height, "video height"))
			return false;
		if (!get_opt_int(argc, argv, &params->fps_num, "video fps num"))
			return false;
		if (!get_opt_int(argc, argv, &params->fps_den, "video fps den"))
			return false;
	}

	if (params->tracks) {
		if (!get_opt_str(argc, argv, &params->acodec, "audio codec"))
			return false;

		audio = calloc(1, sizeof(*audio) * params->tracks);

		for (int i = 0; i < params->tracks; i++) {
			if (!get_audio_params(&audio[i], argc, argv)) {
				free(audio);
				return false;
			}
		}
	}

	*p_audio = audio;

	get_opt_str(argc, argv, &params->muxer_settings, "muxer settings");

	return true;
}