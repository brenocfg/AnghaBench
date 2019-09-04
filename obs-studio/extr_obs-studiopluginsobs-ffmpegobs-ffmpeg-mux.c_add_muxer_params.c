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
struct ffmpeg_muxer {int /*<<< orphan*/  output; } ;
struct dstr {char* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_catf (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  log_muxer_params (struct ffmpeg_muxer*,char*) ; 
 int /*<<< orphan*/  obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_get_settings (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_muxer_params(struct dstr *cmd, struct ffmpeg_muxer *stream)
{
	obs_data_t *settings = obs_output_get_settings(stream->output);
	struct dstr mux = {0};

	dstr_copy(&mux, obs_data_get_string(settings, "muxer_settings"));

	log_muxer_params(stream, mux.array);

	dstr_replace(&mux, "\"", "\\\"");
	obs_data_release(settings);

	dstr_catf(cmd, "\"%s\" ", mux.array ? mux.array : "");

	dstr_free(&mux);
}