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
typedef  int uint64_t ;
struct rtmp_stream {int dbr_data_size; long dbr_est_bitrate; scalar_t__ audio_bitrate; int /*<<< orphan*/  dbr_frames; } ;
struct dbr_frame {int send_end; int send_beg; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  front ;

/* Variables and functions */
 int MAX_ESTIMATE_DURATION_MS ; 
 int MIN_ESTIMATE_DURATION_MS ; 
 int /*<<< orphan*/  circlebuf_peek_front (int /*<<< orphan*/ *,struct dbr_frame*,int) ; 
 int /*<<< orphan*/  circlebuf_pop_front (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  circlebuf_push_back (int /*<<< orphan*/ *,struct dbr_frame*,int) ; 

__attribute__((used)) static void dbr_add_frame(struct rtmp_stream *stream, struct dbr_frame *back)
{
	struct dbr_frame front;
	uint64_t dur;

	circlebuf_push_back(&stream->dbr_frames, back, sizeof(*back));
	circlebuf_peek_front(&stream->dbr_frames, &front, sizeof(front));

	stream->dbr_data_size += back->size;

	dur = (back->send_end - front.send_beg) / 1000000;

	if (dur >= MAX_ESTIMATE_DURATION_MS) {
		stream->dbr_data_size -= front.size;
		circlebuf_pop_front(&stream->dbr_frames, NULL, sizeof(front));
	}

	stream->dbr_est_bitrate =
		(dur >= MIN_ESTIMATE_DURATION_MS)
			? (long)(stream->dbr_data_size * 1000 / dur)
			: 0;
	stream->dbr_est_bitrate *= 8;
	stream->dbr_est_bitrate /= 1000;

	if (stream->dbr_est_bitrate) {
		stream->dbr_est_bitrate -= stream->audio_bitrate;
		if (stream->dbr_est_bitrate < 50)
			stream->dbr_est_bitrate = 50;
	}
}