#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_compr_tstamp {int /*<<< orphan*/  copied_total; int /*<<< orphan*/  byte_offset; } ;
struct snd_compr_stream {scalar_t__ direction; TYPE_1__* runtime; TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* pointer ) (struct snd_compr_stream*,struct snd_compr_tstamp*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  total_bytes_available; int /*<<< orphan*/  total_bytes_transferred; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ SND_COMPRESS_PLAYBACK ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_compr_stream*,struct snd_compr_tstamp*) ; 

__attribute__((used)) static int snd_compr_update_tstamp(struct snd_compr_stream *stream,
		struct snd_compr_tstamp *tstamp)
{
	if (!stream->ops->pointer)
		return -ENOTSUPP;
	stream->ops->pointer(stream, tstamp);
	pr_debug("dsp consumed till %d total %d bytes\n",
		tstamp->byte_offset, tstamp->copied_total);
	if (stream->direction == SND_COMPRESS_PLAYBACK)
		stream->runtime->total_bytes_transferred = tstamp->copied_total;
	else
		stream->runtime->total_bytes_available = tstamp->copied_total;
	return 0;
}