#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {int /*<<< orphan*/  attached_picture; } ;
struct demuxer {TYPE_2__* priv; } ;
struct TYPE_5__ {int num_streams; TYPE_1__* avfc; struct sh_stream** streams; } ;
typedef  TYPE_2__ lavf_priv_t ;
struct TYPE_6__ {int /*<<< orphan*/  discard; } ;
struct TYPE_4__ {TYPE_3__** streams; } ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 int /*<<< orphan*/  AVDISCARD_ALL ; 
 int /*<<< orphan*/  AVDISCARD_DEFAULT ; 
 scalar_t__ demux_stream_is_selected (struct sh_stream*) ; 

__attribute__((used)) static void select_tracks(struct demuxer *demuxer, int start)
{
    lavf_priv_t *priv = demuxer->priv;
    for (int n = start; n < priv->num_streams; n++) {
        struct sh_stream *stream = priv->streams[n];
        AVStream *st = priv->avfc->streams[n];
        bool selected = stream && demux_stream_is_selected(stream) &&
                        !stream->attached_picture;
        st->discard = selected ? AVDISCARD_DEFAULT : AVDISCARD_ALL;
    }
}