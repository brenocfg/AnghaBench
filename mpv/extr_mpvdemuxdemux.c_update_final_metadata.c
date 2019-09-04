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
struct sh_stream {scalar_t__ type; int /*<<< orphan*/  tags; int /*<<< orphan*/  attached_picture; } ;
struct mp_packet_tags {int /*<<< orphan*/  stream; int /*<<< orphan*/  demux; } ;
struct demux_internal {int num_streams; struct sh_stream** streams; TYPE_1__* master_stream; TYPE_2__* d_user; } ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; struct demux_internal* in; } ;
typedef  TYPE_2__ demuxer_t ;
struct TYPE_4__ {struct mp_packet_tags* tags_reader; } ;

/* Variables and functions */
 scalar_t__ STREAM_AUDIO ; 
 scalar_t__ STREAM_VIDEO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_tags_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_tags_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_final_metadata(demuxer_t *demuxer)
{
    assert(demuxer == demuxer->in->d_user);
    struct demux_internal *in = demuxer->in;

    struct mp_packet_tags *tags =
        in->master_stream ? in->master_stream->tags_reader : NULL;

    if (tags)
        mp_tags_replace(demuxer->metadata, tags->demux);

    // Often for useful audio-only files, which have metadata in the audio track
    // metadata instead of the main metadata, but can also have cover art
    // metadata (which libavformat likes to treat as video streams).
    int astreams = 0;
    int astream_id = -1;
    int vstreams = 0;
    for (int n = 0; n < in->num_streams; n++) {
        struct sh_stream *sh = in->streams[n];
        if (sh->type == STREAM_VIDEO && !sh->attached_picture)
            vstreams += 1;
        if (sh->type == STREAM_AUDIO) {
            astreams += 1;
            astream_id = n;
        }
    }
    if (vstreams == 0 && astreams == 1)
        mp_tags_merge(demuxer->metadata, in->streams[astream_id]->tags);

    if (tags)
        mp_tags_merge(demuxer->metadata, tags->stream);
}