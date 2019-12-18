#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int peak_kbps; } ;
struct ftl_stream {int peak_kbps; TYPE_2__ params; int /*<<< orphan*/  ftl_handle; int /*<<< orphan*/  output; } ;
struct TYPE_4__ {int /*<<< orphan*/  ending_rtt; int /*<<< orphan*/  starting_rtt; int /*<<< orphan*/  peak_kbps; scalar_t__ pkts_sent; scalar_t__ lost_pkts; } ;
typedef  TYPE_1__ speed_test_t ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  scalar_t__ ftl_status_t ;

/* Variables and functions */
 scalar_t__ FTL_SUCCESS ; 
 scalar_t__ ftl_ingest_speed_test_ex (int /*<<< orphan*/ *,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ftl_ingest_update_params (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ftl_status_code_to_string (scalar_t__) ; 
 int /*<<< orphan*/  info (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_encoder_get_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_peak_bitrate(struct ftl_stream *stream)
{
	int speedtest_kbps = 15000;
	int speedtest_duration = 1000;
	speed_test_t results;
	ftl_status_t status_code;

	status_code = ftl_ingest_speed_test_ex(&stream->ftl_handle,
					       speedtest_kbps,
					       speedtest_duration, &results);

	float percent_lost = 0;

	if (status_code == FTL_SUCCESS) {
		percent_lost = (float)results.lost_pkts * 100.f /
			       (float)results.pkts_sent;
	} else {
		warn("Speed test failed with: %s",
		     ftl_status_code_to_string(status_code));
	}

	// Get what the user set the encoding bitrate to.
	obs_encoder_t *video_encoder =
		obs_output_get_video_encoder(stream->output);
	obs_data_t *video_settings = obs_encoder_get_settings(video_encoder);
	int user_desired_bitrate =
		(int)obs_data_get_int(video_settings, "bitrate");
	obs_data_release(video_settings);

	// Report the results.
	info("Speed test completed: User desired bitrate %d, Peak kbps %d, "
	     "initial rtt %d, "
	     "final rtt %d, %3.2f lost packets",
	     user_desired_bitrate, results.peak_kbps, results.starting_rtt,
	     results.ending_rtt, percent_lost);

	// We still want to set the peak to about 1.2x what the target bitrate is,
	// even if the speed test reported it should be lower. If we don't, FTL
	// will queue data on the client and start adding latency. If the internet
	// connection really can't handle the bitrate the user will see either lost frame
	// and recovered frame counts go up, which is reflect in the dropped_frames count.
	stream->peak_kbps = stream->params.peak_kbps =
		user_desired_bitrate * 12 / 10;
	ftl_ingest_update_params(&stream->ftl_handle, &stream->params);
}