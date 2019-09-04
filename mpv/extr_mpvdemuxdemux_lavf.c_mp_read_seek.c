#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stream_avseek {int stream_index; int flags; int /*<<< orphan*/  timestamp; } ;
struct stream {int dummy; } ;
struct demuxer {TYPE_1__* priv; } ;
struct TYPE_2__ {struct stream* stream; } ;
typedef  TYPE_1__ lavf_priv_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  STREAM_CTRL_AVSEEK ; 
 scalar_t__ STREAM_OK ; 
 scalar_t__ stream_control (struct stream*,int /*<<< orphan*/ ,struct stream_avseek*) ; 
 int /*<<< orphan*/  stream_drop_buffers (struct stream*) ; 

__attribute__((used)) static int64_t mp_read_seek(void *opaque, int stream_idx, int64_t ts, int flags)
{
    struct demuxer *demuxer = opaque;
    lavf_priv_t *priv = demuxer->priv;
    struct stream *stream = priv->stream;

    struct stream_avseek cmd = {
        .stream_index = stream_idx,
        .timestamp = ts,
        .flags = flags,
    };

    if (stream_control(stream, STREAM_CTRL_AVSEEK, &cmd) == STREAM_OK) {
        stream_drop_buffers(stream);
        return 0;
    }
    return AVERROR(ENOSYS);
}