#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct priv {int seek_reinit; int /*<<< orphan*/  slave; scalar_t__ is_cdda; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream; struct priv* priv; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*,double) ; 
 int SEEK_FACTOR ; 
 int SEEK_FORCE ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_TIME_LENGTH ; 
 int /*<<< orphan*/  STREAM_CTRL_SEEK_TO_TIME ; 
 int /*<<< orphan*/  demux_seek (int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  stream_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  stream_drop_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d_seek(demuxer_t *demuxer, double seek_pts, int flags)
{
    struct priv *p = demuxer->priv;

    if (p->is_cdda) {
        demux_seek(p->slave, seek_pts, flags);
        return;
    }

    if (flags & SEEK_FACTOR) {
        double tmp = 0;
        stream_control(demuxer->stream, STREAM_CTRL_GET_TIME_LENGTH, &tmp);
        seek_pts *= tmp;
    }

    MP_VERBOSE(demuxer, "seek to: %f\n", seek_pts);

    // Supposed to induce a seek reset. Does it even work? I don't know.
    // It will log some bogus error messages, since the demuxer will try a
    // low level seek, which will obviously not work. But it will probably
    // clear its internal buffers.
    demux_seek(p->slave, 0, SEEK_FACTOR | SEEK_FORCE);
    stream_drop_buffers(demuxer->stream);

    double seek_arg[] = {seek_pts, flags};
    stream_control(demuxer->stream, STREAM_CTRL_SEEK_TO_TIME, seek_arg);

    p->seek_reinit = true;
}