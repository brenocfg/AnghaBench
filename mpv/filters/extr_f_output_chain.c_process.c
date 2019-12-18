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
struct mp_frame {scalar_t__ type; } ;
struct mp_filter {int /*<<< orphan*/ * ppins; struct chain* priv; } ;
struct TYPE_2__ {int got_output_eof; int /*<<< orphan*/  update_subtitles_ctx; int /*<<< orphan*/  (* update_subtitles ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct chain {TYPE_1__ public; int /*<<< orphan*/  filters_out; int /*<<< orphan*/  filters_in; } ;

/* Variables and functions */
 scalar_t__ MP_FRAME_EOF ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  MP_VERBOSE (struct chain*,char*) ; 
 int /*<<< orphan*/  mp_frame_get_pts (struct mp_frame) ; 
 scalar_t__ mp_pin_can_transfer_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,struct mp_frame) ; 
 struct mp_frame mp_pin_out_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process(struct mp_filter *f)
{
    struct chain *p = f->priv;

    if (mp_pin_can_transfer_data(p->filters_in, f->ppins[0])) {
        struct mp_frame frame = mp_pin_out_read(f->ppins[0]);

        if (frame.type == MP_FRAME_EOF)
            MP_VERBOSE(p, "filter input EOF\n");

        if (frame.type == MP_FRAME_VIDEO && p->public.update_subtitles) {
            p->public.update_subtitles(p->public.update_subtitles_ctx,
                                       mp_frame_get_pts(frame));
        }

        mp_pin_in_write(p->filters_in, frame);
    }

    if (mp_pin_can_transfer_data(f->ppins[1], p->filters_out)) {
        struct mp_frame frame = mp_pin_out_read(p->filters_out);

        p->public.got_output_eof = frame.type == MP_FRAME_EOF;
        if (p->public.got_output_eof)
            MP_VERBOSE(p, "filter output EOF\n");

        mp_pin_in_write(f->ppins[1], frame);
    }
}