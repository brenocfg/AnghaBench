#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  output; } ;
struct TYPE_9__ {TYPE_1__* array; scalar_t__ num; } ;
struct ffmpeg_output {scalar_t__ stop_ts; TYPE_3__ ff_data; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  write_mutex; TYPE_4__ packets; } ;
struct TYPE_7__ {scalar_t__ size; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_free_packet (TYPE_1__*) ; 
 int av_interleaved_write_frame (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  da_erase (TYPE_4__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffmpeg_log_error (int /*<<< orphan*/ ,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffmpeg_output_full_stop (struct ffmpeg_output*) ; 
 scalar_t__ get_packet_sys_dts (struct ffmpeg_output*,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stopping (struct ffmpeg_output*) ; 

__attribute__((used)) static int process_packet(struct ffmpeg_output *output)
{
	AVPacket packet;
	bool new_packet = false;
	int ret;

	pthread_mutex_lock(&output->write_mutex);
	if (output->packets.num) {
		packet = output->packets.array[0];
		da_erase(output->packets, 0);
		new_packet = true;
	}
	pthread_mutex_unlock(&output->write_mutex);

	if (!new_packet)
		return 0;

	/*blog(LOG_DEBUG, "size = %d, flags = %lX, stream = %d, "
			"packets queued: %lu",
			packet.size, packet.flags,
			packet.stream_index, output->packets.num);*/

	if (stopping(output)) {
		uint64_t sys_ts = get_packet_sys_dts(output, &packet);
		if (sys_ts >= output->stop_ts) {
			ffmpeg_output_full_stop(output);
			return 0;
		}
	}

	output->total_bytes += packet.size;

	ret = av_interleaved_write_frame(output->ff_data.output, &packet);
	if (ret < 0) {
		av_free_packet(&packet);
		ffmpeg_log_error(LOG_WARNING, &output->ff_data,
				 "receive_audio: Error writing packet: %s",
				 av_err2str(ret));
		return ret;
	}

	return 0;
}