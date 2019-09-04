#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mp_frame {scalar_t__ type; int /*<<< orphan*/ * data; } ;
struct mp_filter {int /*<<< orphan*/ * ppins; struct fixed_aframe_size_priv* priv; } ;
struct fixed_aframe_size_priv {scalar_t__ samples; scalar_t__ out_written; int /*<<< orphan*/ * out; int /*<<< orphan*/  pad_silence; int /*<<< orphan*/ * in; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 struct mp_frame MAKE_FRAME (scalar_t__,int /*<<< orphan*/ *) ; 
 int MPMIN (int,scalar_t__) ; 
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*) ; 
 scalar_t__ MP_FRAME_AUDIO ; 
 scalar_t__ MP_FRAME_EOF ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_aframe_config_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_aframe_config_equals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_aframe_copy_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_aframe_copy_samples (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mp_aframe_create () ; 
 int mp_aframe_get_size (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_aframe_pool_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mp_aframe_set_silence (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mp_aframe_set_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_aframe_skip_samples (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (struct mp_filter*) ; 
 int /*<<< orphan*/  mp_pin_in_needs_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,struct mp_frame) ; 
 struct mp_frame mp_pin_out_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_out_repeat_eof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_out_request_data_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_out_unread (int /*<<< orphan*/ ,struct mp_frame) ; 

__attribute__((used)) static void fixed_aframe_size_process(struct mp_filter *f)
{
    struct fixed_aframe_size_priv *p = f->priv;

    if (!mp_pin_in_needs_data(f->ppins[1]))
        return;

    if (p->in && !mp_aframe_get_size(p->in))
        TA_FREEP(&p->in);

    if (!p->in) {
        struct mp_frame frame = mp_pin_out_read(f->ppins[0]);
        if (frame.type == MP_FRAME_EOF) {
            if (!p->out) {
                mp_pin_in_write(f->ppins[1], frame);
                return;
            }
            mp_pin_out_repeat_eof(f->ppins[0]);
        } else if (frame.type == MP_FRAME_AUDIO) {
            p->in = frame.data;
            if (p->out && !mp_aframe_config_equals(p->out, p->in)) {
                mp_pin_out_unread(f->ppins[0], frame);
                p->in = NULL;
            }
        } else if (frame.type) {
            MP_ERR(f, "unsupported frame type\n");
            mp_filter_internal_mark_failed(f);
            return;
        } else {
            return; // no new data yet
        }
    }

    if (p->in) {
        if (!p->out) {
            p->out = mp_aframe_create();
            mp_aframe_config_copy(p->out, p->in);
            mp_aframe_copy_attributes(p->out, p->in);
            if (mp_aframe_pool_allocate(p->pool, p->out, p->samples) < 0) {
                mp_filter_internal_mark_failed(f);
                return;
            }
            p->out_written = 0;
        }
        int in_samples = mp_aframe_get_size(p->in);
        int copy = MPMIN(in_samples, p->samples - p->out_written);
        if (!mp_aframe_copy_samples(p->out, p->out_written, p->in, 0, copy))
            assert(0);
        mp_aframe_skip_samples(p->in, copy);
        p->out_written += copy;
    }

    // p->in not set means draining for EOF or format change
    if ((!p->in && p->out_written) || p->out_written == p->samples) {
        int missing = p->samples - p->out_written;
        assert(missing >= 0);
        if (missing) {
            mp_aframe_set_silence(p->out, p->out_written, missing);
            if (!p->pad_silence)
                mp_aframe_set_size(p->out, p->out_written);
        }
        mp_pin_in_write(f->ppins[1], MAKE_FRAME(MP_FRAME_AUDIO, p->out));
        p->out = NULL;
        p->out_written = 0;
    } else {
        mp_pin_out_request_data_next(f->ppins[0]);
    }
}