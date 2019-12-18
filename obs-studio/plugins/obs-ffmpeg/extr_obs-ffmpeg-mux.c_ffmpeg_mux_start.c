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
struct win_version_info {int major; } ;
struct TYPE_2__ {int /*<<< orphan*/  array; } ;
struct ffmpeg_muxer {TYPE_1__ path; int /*<<< orphan*/  output; scalar_t__ total_bytes; int /*<<< orphan*/  capturing; int /*<<< orphan*/  active; int /*<<< orphan*/  pipe; } ;
struct dstr {char* array; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_win_ver (struct win_version_info*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 char* obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_output_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_can_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_initialize_encoders (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_set_last_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * os_fopen (char const*,char*) ; 
 int /*<<< orphan*/  os_unlink (char const*) ; 
 int /*<<< orphan*/  start_pipe (struct ffmpeg_muxer*,char const*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static bool ffmpeg_mux_start(void *data)
{
	struct ffmpeg_muxer *stream = data;
	obs_data_t *settings;
	const char *path;

	if (!obs_output_can_begin_data_capture(stream->output, 0))
		return false;
	if (!obs_output_initialize_encoders(stream->output, 0))
		return false;

	settings = obs_output_get_settings(stream->output);
	path = obs_data_get_string(settings, "path");

	/* ensure output path is writable to avoid generic error message */
	/* TODO: remove once ffmpeg-mux is refactored to pass errors back */
	FILE *test_file = os_fopen(path, "wb");
	if (!test_file) {
		struct dstr error_message;
		dstr_init_copy(&error_message,
			       obs_module_text("UnableToWritePath"));
#ifdef _WIN32
		// special warning for Windows 10 users about Defender
		struct win_version_info ver;
		get_win_ver(&ver);
		if (ver.major >= 10) {
			dstr_cat(&error_message, "\n\n");
			dstr_cat(&error_message,
				 obs_module_text("WarnWindowsDefender"));
		}
#endif
		dstr_replace(&error_message, "%1", path);
		obs_output_set_last_error(stream->output, error_message.array);
		dstr_free(&error_message);
		obs_data_release(settings);
		return false;
	}

	fclose(test_file);
	os_unlink(path);

	start_pipe(stream, path);
	obs_data_release(settings);

	if (!stream->pipe) {
		obs_output_set_last_error(
			stream->output, obs_module_text("HelperProcessFailed"));
		warn("Failed to create process pipe");
		return false;
	}

	/* write headers and start capture */
	os_atomic_set_bool(&stream->active, true);
	os_atomic_set_bool(&stream->capturing, true);
	stream->total_bytes = 0;
	obs_output_begin_data_capture(stream->output, 0);

	info("Writing file '%s'...", stream->path.array);
	return true;
}