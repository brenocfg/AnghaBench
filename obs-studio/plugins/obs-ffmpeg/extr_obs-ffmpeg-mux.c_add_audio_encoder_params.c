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
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  audio_t ;

/* Variables and functions */
 scalar_t__ audio_output_get_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dstr_catf (struct dstr*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_encoder_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ obs_encoder_get_sample_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_encoder_get_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_get_audio () ; 

__attribute__((used)) static void add_audio_encoder_params(struct dstr *cmd, obs_encoder_t *aencoder)
{
	obs_data_t *settings = obs_encoder_get_settings(aencoder);
	int bitrate = (int)obs_data_get_int(settings, "bitrate");
	audio_t *audio = obs_get_audio();
	struct dstr name = {0};

	obs_data_release(settings);

	dstr_copy(&name, obs_encoder_get_name(aencoder));
	dstr_replace(&name, "\"", "\"\"");

	dstr_catf(cmd, "\"%s\" %d %d %d ", name.array, bitrate,
		  (int)obs_encoder_get_sample_rate(aencoder),
		  (int)audio_output_get_channels(audio));

	dstr_free(&name);
}