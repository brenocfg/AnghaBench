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
struct sst_hsw_stream {int play_silence; } ;
struct sst_hsw {int dummy; } ;

/* Variables and functions */

bool sst_hsw_stream_get_silence_start(struct sst_hsw *hsw,
	struct sst_hsw_stream *stream)
{
	return stream->play_silence;
}