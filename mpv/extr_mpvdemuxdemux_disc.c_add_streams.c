#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {scalar_t__ type; int demuxer_id; TYPE_1__* codec; } ;
struct priv {int num_streams; int /*<<< orphan*/  is_dvd; int /*<<< orphan*/  streams; struct sh_stream** dvd_subs; int /*<<< orphan*/  slave; } ;
struct mp_image_params {int /*<<< orphan*/  p_h; int /*<<< orphan*/  p_w; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_7__ {int /*<<< orphan*/  stream; struct priv* priv; } ;
typedef  TYPE_2__ demuxer_t ;
struct TYPE_6__ {int /*<<< orphan*/  par_h; int /*<<< orphan*/  par_w; int /*<<< orphan*/  disp_h; int /*<<< orphan*/  disp_w; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct priv*,int /*<<< orphan*/ ,int,struct sh_stream*) ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_ASPECT_RATIO ; 
 scalar_t__ STREAM_OK ; 
 scalar_t__ STREAM_SUB ; 
 scalar_t__ STREAM_VIDEO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  demux_add_sh_stream (TYPE_2__*,struct sh_stream*) ; 
 struct sh_stream* demux_alloc_sh_stream (scalar_t__) ; 
 int demux_get_num_stream (int /*<<< orphan*/ ) ; 
 struct sh_stream* demux_get_stream (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_disc_lang (int /*<<< orphan*/ ,struct sh_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_params_set_dsize (struct mp_image_params*,int,int) ; 
 int /*<<< orphan*/  reselect_streams (TYPE_2__*) ; 
 scalar_t__ stream_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static void add_streams(demuxer_t *demuxer)
{
    struct priv *p = demuxer->priv;

    for (int n = p->num_streams; n < demux_get_num_stream(p->slave); n++) {
        struct sh_stream *src = demux_get_stream(p->slave, n);
        if (src->type == STREAM_SUB) {
            struct sh_stream *sub = NULL;
            if (src->demuxer_id >= 0x20 && src->demuxer_id <= 0x3F)
                sub = p->dvd_subs[src->demuxer_id - 0x20];
            if (sub) {
                assert(p->num_streams == n); // directly mapped
                MP_TARRAY_APPEND(p, p->streams, p->num_streams, sub);
                continue;
            }
        }
        struct sh_stream *sh = demux_alloc_sh_stream(src->type);
        assert(p->num_streams == n); // directly mapped
        MP_TARRAY_APPEND(p, p->streams, p->num_streams, sh);
        // Copy all stream fields that might be relevant
        *sh->codec = *src->codec;
        sh->demuxer_id = src->demuxer_id;
        if (src->type == STREAM_VIDEO) {
            double ar;
            if (stream_control(demuxer->stream, STREAM_CTRL_GET_ASPECT_RATIO, &ar)
                                == STREAM_OK)
            {
                struct mp_image_params f = {.w = src->codec->disp_w,
                                            .h = src->codec->disp_h};
                mp_image_params_set_dsize(&f, 1728 * ar, 1728);
                sh->codec->par_w = f.p_w;
                sh->codec->par_h = f.p_h;
            }
        }
        get_disc_lang(demuxer->stream, sh, p->is_dvd);
        demux_add_sh_stream(demuxer, sh);
    }
    reselect_streams(demuxer);
}