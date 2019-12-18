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
struct TYPE_2__ {int /*<<< orphan*/  array; } ;
struct flv_output {int got_first_video; int sent_headers; TYPE_1__ path; int /*<<< orphan*/  output; int /*<<< orphan*/  active; int /*<<< orphan*/  file; int /*<<< orphan*/  stopping; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_copy (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_output_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_can_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_initialize_encoders (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool flv_output_start(void *data)
{
	struct flv_output *stream = data;
	obs_data_t *settings;
	const char *path;

	if (!obs_output_can_begin_data_capture(stream->output, 0))
		return false;
	if (!obs_output_initialize_encoders(stream->output, 0))
		return false;

	stream->got_first_video = false;
	stream->sent_headers = false;
	os_atomic_set_bool(&stream->stopping, false);

	/* get path */
	settings = obs_output_get_settings(stream->output);
	path = obs_data_get_string(settings, "path");
	dstr_copy(&stream->path, path);
	obs_data_release(settings);

	stream->file = os_fopen(stream->path.array, "wb");
	if (!stream->file) {
		warn("Unable to open FLV file '%s'", stream->path.array);
		return false;
	}

	/* write headers and start capture */
	os_atomic_set_bool(&stream->active, true);
	obs_output_begin_data_capture(stream->output, 0);

	info("Writing FLV file '%s'...", stream->path.array);
	return true;
}