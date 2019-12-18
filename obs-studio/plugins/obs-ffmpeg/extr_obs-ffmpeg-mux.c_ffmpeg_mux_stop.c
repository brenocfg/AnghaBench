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
struct ffmpeg_muxer {long long stop_ts; int /*<<< orphan*/  capturing; int /*<<< orphan*/  stopping; } ;
typedef  long long int64_t ;

/* Variables and functions */
 scalar_t__ capturing (struct ffmpeg_muxer*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ffmpeg_mux_stop(void *data, uint64_t ts)
{
	struct ffmpeg_muxer *stream = data;

	if (capturing(stream) || ts == 0) {
		stream->stop_ts = (int64_t)ts / 1000LL;
		os_atomic_set_bool(&stream->stopping, true);
		os_atomic_set_bool(&stream->capturing, false);
	}
}