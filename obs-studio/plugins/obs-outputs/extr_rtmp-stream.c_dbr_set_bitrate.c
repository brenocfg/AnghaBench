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
struct rtmp_stream {int /*<<< orphan*/  dbr_cur_bitrate; int /*<<< orphan*/  output; } ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_encoder_get_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_encoder_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dbr_set_bitrate(struct rtmp_stream *stream)
{
	obs_encoder_t *vencoder = obs_output_get_video_encoder(stream->output);
	obs_data_t *settings = obs_encoder_get_settings(vencoder);

	obs_data_set_int(settings, "bitrate", stream->dbr_cur_bitrate);
	obs_encoder_update(vencoder, settings);

	obs_data_release(settings);
}