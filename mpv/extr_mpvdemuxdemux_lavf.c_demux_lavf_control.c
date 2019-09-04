#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {int demuxer_id; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int cur_program; int own_stream; int /*<<< orphan*/  stream; TYPE_9__* avfc; struct sh_stream** streams; } ;
typedef  TYPE_1__ lavf_priv_t ;
struct TYPE_12__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  metadata; TYPE_1__* priv; } ;
typedef  TYPE_2__ demuxer_t ;
struct TYPE_13__ {int vid; int aid; int sid; int progid; } ;
typedef  TYPE_3__ demux_program_t ;
struct TYPE_15__ {int nb_programs; int /*<<< orphan*/  pb; TYPE_4__** programs; } ;
struct TYPE_14__ {int id; int nb_stream_indexes; size_t* stream_index; int /*<<< orphan*/  metadata; } ;
typedef  TYPE_4__ AVProgram ;

/* Variables and functions */
 int CONTROL_FALSE ; 
 int CONTROL_OK ; 
 int CONTROL_UNKNOWN ; 
#define  DEMUXER_CTRL_IDENTIFY_PROGRAM 134 
#define  DEMUXER_CTRL_REPLACE_STREAM 133 
#define  DEMUXER_CTRL_RESYNC 132 
#define  DEMUXER_CTRL_SWITCHED_TRACKS 131 
#define  STREAM_AUDIO 130 
#define  STREAM_SUB 129 
#define  STREAM_VIDEO 128 
 int /*<<< orphan*/  add_new_streams (TYPE_2__*) ; 
 int /*<<< orphan*/  avformat_flush (TYPE_9__*) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demux_metadata_changed (TYPE_2__*) ; 
 int /*<<< orphan*/  free_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_tags_copy_from_av_dictionary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_tracks (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_drop_buffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_metadata (TYPE_2__*) ; 

__attribute__((used)) static int demux_lavf_control(demuxer_t *demuxer, int cmd, void *arg)
{
    lavf_priv_t *priv = demuxer->priv;

    switch (cmd) {
    case DEMUXER_CTRL_SWITCHED_TRACKS:
    {
        select_tracks(demuxer, 0);
        return CONTROL_OK;
    }
    case DEMUXER_CTRL_IDENTIFY_PROGRAM:
    {
        demux_program_t *prog = arg;
        AVProgram *program;
        int p, i;
        int start;

        add_new_streams(demuxer);

        prog->vid = prog->aid = prog->sid = -2;
        if (priv->avfc->nb_programs < 1)
            return CONTROL_FALSE;

        if (prog->progid == -1) {
            p = 0;
            while (p < priv->avfc->nb_programs && priv->avfc->programs[p]->id != priv->cur_program)
                p++;
            p = (p + 1) % priv->avfc->nb_programs;
        } else {
            for (i = 0; i < priv->avfc->nb_programs; i++)
                if (priv->avfc->programs[i]->id == prog->progid)
                    break;
            if (i == priv->avfc->nb_programs)
                return CONTROL_FALSE;
            p = i;
        }
        start = p;
redo:
        prog->vid = prog->aid = prog->sid = -2;
        program = priv->avfc->programs[p];
        for (i = 0; i < program->nb_stream_indexes; i++) {
            struct sh_stream *stream = priv->streams[program->stream_index[i]];
            if (stream) {
                switch (stream->type) {
                case STREAM_VIDEO:
                    if (prog->vid == -2)
                        prog->vid = stream->demuxer_id;
                    break;
                case STREAM_AUDIO:
                    if (prog->aid == -2)
                        prog->aid = stream->demuxer_id;
                    break;
                case STREAM_SUB:
                    if (prog->sid == -2)
                        prog->sid = stream->demuxer_id;
                    break;
                }
            }
        }
        if (prog->progid == -1 && prog->vid == -2 && prog->aid == -2) {
            p = (p + 1) % priv->avfc->nb_programs;
            if (p == start)
                return CONTROL_FALSE;
            goto redo;
        }
        priv->cur_program = prog->progid = program->id;

        mp_tags_copy_from_av_dictionary(demuxer->metadata, priv->avfc->programs[p]->metadata);
        update_metadata(demuxer);
        // Enforce metadata update even if no explicit METADATA_UPDATED since we switched program.
        demux_metadata_changed(demuxer);

        return CONTROL_OK;
    }
    case DEMUXER_CTRL_RESYNC:
        stream_drop_buffers(priv->stream);
        avio_flush(priv->avfc->pb);
        avformat_flush(priv->avfc);
        return CONTROL_OK;
    case DEMUXER_CTRL_REPLACE_STREAM:
        if (priv->own_stream)
            free_stream(priv->stream);
        priv->own_stream = false;
        priv->stream = demuxer->stream;
        return CONTROL_OK;
    default:
        return CONTROL_UNKNOWN;
    }
}