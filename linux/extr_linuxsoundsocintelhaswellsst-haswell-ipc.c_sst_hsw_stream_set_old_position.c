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
struct sst_hsw_stream {int /*<<< orphan*/  old_position; } ;
struct sst_hsw {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */

void sst_hsw_stream_set_old_position(struct sst_hsw *hsw,
	struct sst_hsw_stream *stream, snd_pcm_uframes_t val)
{
	stream->old_position = val;
}