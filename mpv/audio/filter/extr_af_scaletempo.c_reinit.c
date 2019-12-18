#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct priv {float frames_stride; int bytes_stride; int bytes_standing; int samples_standing; int bytes_overlap; int samples_overlap; char* buf_overlap; char* table_blend; float frames_search; char* buf_pre_corr; char* table_window; int bytes_per_frame; int num_channels; int bytes_queue; char* buf_queue; int /*<<< orphan*/  in; int /*<<< orphan*/  cur_format; int /*<<< orphan*/  frames_stride_scaled; scalar_t__ bytes_to_slide; scalar_t__ bytes_queued; int /*<<< orphan*/ * best_overlap_offset; TYPE_1__* opts; int /*<<< orphan*/ * output_overlap; int /*<<< orphan*/  speed; } ;
struct mp_filter {struct priv* priv; } ;
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_2__ {float ms_stride; int percent_overlap; float ms_search; } ;

/* Variables and functions */
 int AF_FORMAT_FLOAT ; 
 int AF_FORMAT_S16 ; 
 int /*<<< orphan*/  MP_DBG (struct mp_filter*,char*,int /*<<< orphan*/ ,int,int,int,int,int,char*) ; 
 int /*<<< orphan*/  MP_FATAL (struct mp_filter*,char*) ; 
 int UNROLL_PADDING ; 
 int /*<<< orphan*/ * best_overlap_offset_float ; 
 int /*<<< orphan*/ * best_overlap_offset_s16 ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_aframe_config_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_aframe_get_channels (int /*<<< orphan*/ ) ; 
 int mp_aframe_get_format (int /*<<< orphan*/ ) ; 
 double mp_aframe_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_aframe_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * output_overlap_float ; 
 int /*<<< orphan*/ * output_overlap_s16 ; 
 void* realloc (char*,int) ; 
 int /*<<< orphan*/  update_speed (struct priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool reinit(struct mp_filter *f)
{
    struct priv *s = f->priv;

    mp_aframe_reset(s->cur_format);

    float srate  = mp_aframe_get_rate(s->in) / 1000.0;
    int nch = mp_aframe_get_channels(s->in);
    int format = mp_aframe_get_format(s->in);

    int use_int = 0;
    if (format == AF_FORMAT_S16) {
        use_int = 1;
    } else if (format != AF_FORMAT_FLOAT) {
        return false;
    }
    int bps = use_int ? 2 : 4;

    s->frames_stride        = srate * s->opts->ms_stride;
    s->bytes_stride         = s->frames_stride * bps * nch;

    update_speed(s, s->speed);

    int frames_overlap = s->frames_stride * s->opts->percent_overlap;
    if (frames_overlap <= 0) {
        s->bytes_standing   = s->bytes_stride;
        s->samples_standing = s->bytes_standing / bps;
        s->output_overlap   = NULL;
        s->bytes_overlap    = 0;
    } else {
        s->samples_overlap  = frames_overlap * nch;
        s->bytes_overlap    = frames_overlap * nch * bps;
        s->bytes_standing   = s->bytes_stride - s->bytes_overlap;
        s->samples_standing = s->bytes_standing / bps;
        s->buf_overlap      = realloc(s->buf_overlap, s->bytes_overlap);
        s->table_blend      = realloc(s->table_blend, s->bytes_overlap * 4);
        if (!s->buf_overlap || !s->table_blend) {
            MP_FATAL(f, "Out of memory\n");
            return false;
        }
        memset(s->buf_overlap, 0, s->bytes_overlap);
        if (use_int) {
            int32_t *pb = s->table_blend;
            int64_t blend = 0;
            for (int i = 0; i < frames_overlap; i++) {
                int32_t v = blend / frames_overlap;
                for (int j = 0; j < nch; j++)
                    *pb++ = v;
                blend += 65536; // 2^16
            }
            s->output_overlap = output_overlap_s16;
        } else {
            float *pb = s->table_blend;
            for (int i = 0; i < frames_overlap; i++) {
                float v = i / (float)frames_overlap;
                for (int j = 0; j < nch; j++)
                    *pb++ = v;
            }
            s->output_overlap = output_overlap_float;
        }
    }

    s->frames_search = (frames_overlap > 1) ? srate * s->opts->ms_search : 0;
    if (s->frames_search <= 0)
        s->best_overlap_offset = NULL;
    else {
        if (use_int) {
            int64_t t = frames_overlap;
            int32_t n = 8589934588LL / (t * t); // 4 * (2^31 - 1) / t^2
            s->buf_pre_corr = realloc(s->buf_pre_corr,
                                        s->bytes_overlap * 2 + UNROLL_PADDING);
            s->table_window = realloc(s->table_window,
                                        s->bytes_overlap * 2 - nch * bps * 2);
            if (!s->buf_pre_corr || !s->table_window) {
                MP_FATAL(f, "Out of memory\n");
                return false;
            }
            memset((char *)s->buf_pre_corr + s->bytes_overlap * 2, 0,
                    UNROLL_PADDING);
            int32_t *pw = s->table_window;
            for (int i = 1; i < frames_overlap; i++) {
                int32_t v = (i * (t - i) * n) >> 15;
                for (int j = 0; j < nch; j++)
                    *pw++ = v;
            }
            s->best_overlap_offset = best_overlap_offset_s16;
        } else {
            s->buf_pre_corr = realloc(s->buf_pre_corr, s->bytes_overlap);
            s->table_window = realloc(s->table_window,
                                        s->bytes_overlap - nch * bps);
            if (!s->buf_pre_corr || !s->table_window) {
                MP_FATAL(f, "Out of memory\n");
                return false;
            }
            float *pw = s->table_window;
            for (int i = 1; i < frames_overlap; i++) {
                float v = i * (frames_overlap - i);
                for (int j = 0; j < nch; j++)
                    *pw++ = v;
            }
            s->best_overlap_offset = best_overlap_offset_float;
        }
    }

    s->bytes_per_frame = bps * nch;
    s->num_channels    = nch;

    s->bytes_queue = (s->frames_search + s->frames_stride + frames_overlap)
                        * bps * nch;
    s->buf_queue = realloc(s->buf_queue, s->bytes_queue + UNROLL_PADDING);
    if (!s->buf_queue) {
        MP_FATAL(f, "Out of memory\n");
        return false;
    }

    s->bytes_queued = 0;
    s->bytes_to_slide = 0;

    MP_DBG(f, ""
           "%.2f stride_in, %i stride_out, %i standing, "
           "%i overlap, %i search, %i queue, %s mode\n",
           s->frames_stride_scaled,
           (int)(s->bytes_stride / nch / bps),
           (int)(s->bytes_standing / nch / bps),
           (int)(s->bytes_overlap / nch / bps),
           s->frames_search,
           (int)(s->bytes_queue / nch / bps),
           (use_int ? "s16" : "float"));

    mp_aframe_config_copy(s->cur_format, s->in);

    return true;
}