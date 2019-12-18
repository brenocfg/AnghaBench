#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {scalar_t__ type; TYPE_1__* codec; int /*<<< orphan*/  tags; } ;
struct replaygain_data {int dummy; } ;
struct demux_internal {int num_streams; struct sh_stream** streams; } ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  log; struct demux_internal* in; } ;
typedef  TYPE_2__ demuxer_t ;
struct TYPE_4__ {int /*<<< orphan*/  replaygain_data; } ;

/* Variables and functions */
 scalar_t__ STREAM_AUDIO ; 
 struct replaygain_data* decode_rgain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_steal (struct demux_internal*,struct replaygain_data*) ; 

__attribute__((used)) static void demux_update_replaygain(demuxer_t *demuxer)
{
    struct demux_internal *in = demuxer->in;
    for (int n = 0; n < in->num_streams; n++) {
        struct sh_stream *sh = in->streams[n];
        if (sh->type == STREAM_AUDIO && !sh->codec->replaygain_data) {
            struct replaygain_data *rg = decode_rgain(demuxer->log, sh->tags);
            if (!rg)
                rg = decode_rgain(demuxer->log, demuxer->metadata);
            if (rg)
                sh->codec->replaygain_data = talloc_steal(in, rg);
        }
    }
}