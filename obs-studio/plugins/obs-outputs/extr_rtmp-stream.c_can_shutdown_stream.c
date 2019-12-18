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
typedef  scalar_t__ uint64_t ;
struct rtmp_stream {scalar_t__ shutdown_timeout_ts; scalar_t__ stop_ts; int /*<<< orphan*/  max_shutdown_time_sec; } ;
struct encoder_packet {scalar_t__ sys_dts_usec; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_gettime_ns () ; 

__attribute__((used)) static inline bool can_shutdown_stream(struct rtmp_stream *stream,
				       struct encoder_packet *packet)
{
	uint64_t cur_time = os_gettime_ns();
	bool timeout = cur_time >= stream->shutdown_timeout_ts;

	if (timeout)
		info("Stream shutdown timeout reached (%d second(s))",
		     stream->max_shutdown_time_sec);

	return timeout || packet->sys_dts_usec >= (int64_t)stream->stop_ts;
}