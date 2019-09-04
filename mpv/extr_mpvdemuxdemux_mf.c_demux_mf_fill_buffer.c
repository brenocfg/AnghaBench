#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct stream {int dummy; } ;
struct TYPE_12__ {size_t curr_frame; size_t nr_of_files; char** names; TYPE_9__* sh; struct stream** streams; } ;
typedef  TYPE_2__ mf_t ;
struct TYPE_13__ {int /*<<< orphan*/  global; TYPE_2__* priv; } ;
typedef  TYPE_3__ demuxer_t ;
struct TYPE_14__ {int pts; int keyframe; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_4__ demux_packet_t ;
struct TYPE_15__ {int /*<<< orphan*/  start; scalar_t__ len; } ;
typedef  TYPE_5__ bstr ;
struct TYPE_16__ {TYPE_1__* codec; } ;
struct TYPE_11__ {int fps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MF_MAX_FILE_SIZE ; 
 int /*<<< orphan*/  demux_add_packet (TYPE_9__*,TYPE_4__*) ; 
 int /*<<< orphan*/  free_stream (struct stream*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* new_demux_packet (scalar_t__) ; 
 struct stream* stream_open (char*,int /*<<< orphan*/ ) ; 
 TYPE_5__ stream_read_complete (struct stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_seek (struct stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int demux_mf_fill_buffer(demuxer_t *demuxer)
{
    mf_t *mf = demuxer->priv;
    if (mf->curr_frame >= mf->nr_of_files)
        return 0;

    struct stream *entry_stream = NULL;
    if (mf->streams)
        entry_stream = mf->streams[mf->curr_frame];
    struct stream *stream = entry_stream;
    if (!stream) {
        char *filename = mf->names[mf->curr_frame];
        if (filename)
            stream = stream_open(filename, demuxer->global);
    }

    if (stream) {
        stream_seek(stream, 0);
        bstr data = stream_read_complete(stream, NULL, MF_MAX_FILE_SIZE);
        if (data.len) {
            demux_packet_t *dp = new_demux_packet(data.len);
            if (dp) {
                memcpy(dp->buffer, data.start, data.len);
                dp->pts = mf->curr_frame / mf->sh->codec->fps;
                dp->keyframe = true;
                demux_add_packet(mf->sh, dp);
            }
        }
        talloc_free(data.start);
    }

    if (stream && stream != entry_stream)
        free_stream(stream);

    mf->curr_frame++;
    return 1;
}