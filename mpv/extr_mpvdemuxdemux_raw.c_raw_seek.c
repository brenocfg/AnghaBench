#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {double frame_rate; double frame_size; } ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  double int64_t ;
struct TYPE_3__ {int /*<<< orphan*/ * stream; struct priv* priv; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int SEEK_FACTOR ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_SIZE ; 
 int /*<<< orphan*/  stream_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  stream_seek (int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static void raw_seek(demuxer_t *demuxer, double seek_pts, int flags)
{
    struct priv *p = demuxer->priv;
    stream_t *s = demuxer->stream;
    int64_t end = 0;
    stream_control(s, STREAM_CTRL_GET_SIZE, &end);
    int64_t pos = seek_pts * p->frame_rate * p->frame_size;
    if (flags & SEEK_FACTOR)
        pos = end * seek_pts;
    if (pos < 0)
        pos = 0;
    if (end && pos > end)
        pos = end;
    stream_seek(s, (pos / p->frame_size) * p->frame_size);
}