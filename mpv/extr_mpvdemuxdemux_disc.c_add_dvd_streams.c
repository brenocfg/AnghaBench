#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stream_dvd_info_req {int* palette; int /*<<< orphan*/  num_subs; } ;
struct stream {int dummy; } ;
struct sh_stream {int demuxer_id; TYPE_1__* codec; } ;
struct priv {struct sh_stream** dvd_subs; int /*<<< orphan*/  is_dvd; } ;
struct mp_csp_params {int dummy; } ;
struct mp_cmat {int dummy; } ;
struct TYPE_6__ {struct stream* stream; struct priv* priv; } ;
typedef  TYPE_2__ demuxer_t ;
struct TYPE_5__ {char* codec; char* extradata; int /*<<< orphan*/  extradata_size; } ;

/* Variables and functions */
 int MPMIN (int,int /*<<< orphan*/ ) ; 
 struct mp_csp_params MP_CSP_PARAMS_DEFAULTS ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_DVD_INFO ; 
 int /*<<< orphan*/  STREAM_SUB ; 
 int /*<<< orphan*/  demux_add_sh_stream (TYPE_2__*,struct sh_stream*) ; 
 struct sh_stream* demux_alloc_sh_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_disc_lang (struct stream*,struct sh_stream*,int) ; 
 int /*<<< orphan*/  mp_get_csp_matrix (struct mp_csp_params*,struct mp_cmat*) ; 
 int /*<<< orphan*/  mp_map_fixp_color (struct mp_cmat*,int,int*,int,int*) ; 
 scalar_t__ stream_control (struct stream*,int /*<<< orphan*/ ,struct stream_dvd_info_req*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* talloc_asprintf_append (char*,char*,...) ; 
 char* talloc_strdup (struct sh_stream*,char*) ; 

__attribute__((used)) static void add_dvd_streams(demuxer_t *demuxer)
{
    struct priv *p = demuxer->priv;
    struct stream *stream = demuxer->stream;
    if (!p->is_dvd)
        return;
    struct stream_dvd_info_req info;
    if (stream_control(stream, STREAM_CTRL_GET_DVD_INFO, &info) > 0) {
        for (int n = 0; n < MPMIN(32, info.num_subs); n++) {
            struct sh_stream *sh = demux_alloc_sh_stream(STREAM_SUB);
            sh->demuxer_id = n + 0x20;
            sh->codec->codec = "dvd_subtitle";
            get_disc_lang(stream, sh, true);
            // p->streams _must_ match with p->slave->streams, so we can't add
            // it yet - it has to be done when the real stream appears, which
            // could be right on start, or any time later.
            p->dvd_subs[n] = sh;

            // emulate the extradata
            struct mp_csp_params csp = MP_CSP_PARAMS_DEFAULTS;
            struct mp_cmat cmatrix;
            mp_get_csp_matrix(&csp, &cmatrix);

            char *s = talloc_strdup(sh, "");
            s = talloc_asprintf_append(s, "palette: ");
            for (int i = 0; i < 16; i++) {
                int color = info.palette[i];
                int y[3] = {(color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff};
                int c[3];
                mp_map_fixp_color(&cmatrix, 8, y, 8, c);
                color = (c[2] << 16) | (c[1] << 8) | c[0];

                if (i != 0)
                    s = talloc_asprintf_append(s, ", ");
                s = talloc_asprintf_append(s, "%06x", color);
            }
            s = talloc_asprintf_append(s, "\n");

            sh->codec->extradata = s;
            sh->codec->extradata_size = strlen(s);

            demux_add_sh_stream(demuxer, sh);
        }
    }
}