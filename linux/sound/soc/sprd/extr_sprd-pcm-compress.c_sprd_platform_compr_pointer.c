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
struct sprd_compr_stream {int /*<<< orphan*/  copied_total; scalar_t__ info_area; } ;
struct sprd_compr_playinfo {int /*<<< orphan*/  current_data_offset; } ;
struct snd_compr_tstamp {int /*<<< orphan*/  pcm_io_frames; int /*<<< orphan*/  copied_total; } ;
struct snd_compr_stream {struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct sprd_compr_stream* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int sprd_platform_compr_pointer(struct snd_compr_stream *cstream,
				       struct snd_compr_tstamp *tstamp)
{
	struct snd_compr_runtime *runtime = cstream->runtime;
	struct sprd_compr_stream *stream = runtime->private_data;
	struct sprd_compr_playinfo *info =
		(struct sprd_compr_playinfo *)stream->info_area;

	tstamp->copied_total = stream->copied_total;
	tstamp->pcm_io_frames = info->current_data_offset;

	return 0;
}