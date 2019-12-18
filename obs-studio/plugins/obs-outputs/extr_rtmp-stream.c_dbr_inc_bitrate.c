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
struct rtmp_stream {scalar_t__ dbr_prev_bitrate; scalar_t__ dbr_cur_bitrate; scalar_t__ dbr_inc_bitrate; scalar_t__ dbr_orig_bitrate; scalar_t__ dbr_inc_timeout; } ;

/* Variables and functions */
 scalar_t__ DBR_INC_TIMER ; 
 int /*<<< orphan*/  info (char*,scalar_t__) ; 
 scalar_t__ os_gettime_ns () ; 

__attribute__((used)) static void dbr_inc_bitrate(struct rtmp_stream *stream)
{
	stream->dbr_prev_bitrate = stream->dbr_cur_bitrate;
	stream->dbr_cur_bitrate += stream->dbr_inc_bitrate;

	if (stream->dbr_cur_bitrate >= stream->dbr_orig_bitrate) {
		stream->dbr_cur_bitrate = stream->dbr_orig_bitrate;
		info("bitrate increased to: %ld, done",
		     stream->dbr_cur_bitrate);
	} else if (stream->dbr_cur_bitrate < stream->dbr_orig_bitrate) {
		stream->dbr_inc_timeout = os_gettime_ns() + DBR_INC_TIMER;
		info("bitrate increased to: %ld, waiting",
		     stream->dbr_cur_bitrate);
	}
}