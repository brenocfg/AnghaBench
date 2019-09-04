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
struct sh_stream {int default_track; TYPE_1__* ds; TYPE_2__* codec; } ;
struct TYPE_4__ {char* codec; } ;
struct TYPE_3__ {int ignore_eof; int /*<<< orphan*/  in; struct sh_stream* cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_SUB ; 
 int /*<<< orphan*/  demux_add_sh_stream_locked (int /*<<< orphan*/ ,struct sh_stream*) ; 
 struct sh_stream* demux_alloc_sh_stream (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sh_stream *demuxer_get_cc_track_locked(struct sh_stream *stream)
{
    struct sh_stream *sh = stream->ds->cc;

    if (!sh) {
        sh = demux_alloc_sh_stream(STREAM_SUB);
        if (!sh)
            return NULL;
        sh->codec->codec = "eia_608";
        sh->default_track = true;
        stream->ds->cc = sh;
        demux_add_sh_stream_locked(stream->ds->in, sh);
        sh->ds->ignore_eof = true;
    }

    return sh;
}