#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stream {int dummy; } ;
struct TYPE_7__ {int avif_flags; TYPE_5__* avfc; scalar_t__ seek_delay; struct stream* stream; } ;
typedef  TYPE_1__ lavf_priv_t ;
typedef  double int64_t ;
struct TYPE_8__ {scalar_t__ ts_resets_possible; TYPE_1__* priv; } ;
typedef  TYPE_2__ demuxer_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {double duration; } ;

/* Variables and functions */
 int AVFMT_NO_BYTE_SEEK ; 
 int AVSEEK_FLAG_BACKWARD ; 
 int AVSEEK_FLAG_BYTE ; 
 double AV_NOPTS_VALUE ; 
 double AV_TIME_BASE ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,char*) ; 
 int SEEK_FACTOR ; 
 int SEEK_FORWARD ; 
 int av_seek_frame (TYPE_5__*,int,double,int) ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 double stream_get_size (struct stream*) ; 
 int /*<<< orphan*/  update_read_stats (TYPE_2__*) ; 

__attribute__((used)) static void demux_seek_lavf(demuxer_t *demuxer, double seek_pts, int flags)
{
    lavf_priv_t *priv = demuxer->priv;
    int avsflags = 0;
    int64_t seek_pts_av = 0;

    if (!(flags & SEEK_FORWARD))
        avsflags = AVSEEK_FLAG_BACKWARD;

    if (flags & SEEK_FACTOR) {
        struct stream *s = priv->stream;
        int64_t end = stream_get_size(s);
        if (end > 0 && demuxer->ts_resets_possible &&
            !(priv->avif_flags & AVFMT_NO_BYTE_SEEK))
        {
            avsflags |= AVSEEK_FLAG_BYTE;
            seek_pts_av = end * seek_pts;
        } else if (priv->avfc->duration != 0 &&
                   priv->avfc->duration != AV_NOPTS_VALUE)
        {
            seek_pts_av = seek_pts * priv->avfc->duration;
        }
    } else {
        if (!(flags & SEEK_FORWARD))
            seek_pts -= priv->seek_delay;
        seek_pts_av = seek_pts * AV_TIME_BASE;
    }

    int r = av_seek_frame(priv->avfc, -1, seek_pts_av, avsflags);
    if (r < 0 && (avsflags & AVSEEK_FLAG_BACKWARD)) {
        // When seeking before the beginning of the file, and seeking fails,
        // try again without the backwards flag to make it seek to the
        // beginning.
        avsflags &= ~AVSEEK_FLAG_BACKWARD;
        r = av_seek_frame(priv->avfc, -1, seek_pts_av, avsflags);
    }

    if (r < 0) {
        char buf[180];
        av_strerror(r, buf, sizeof(buf));
        MP_VERBOSE(demuxer, "Seek failed (%s)\n", buf);
    }

    update_read_stats(demuxer);
}