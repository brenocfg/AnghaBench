#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mp_frame {scalar_t__ type; } ;
struct TYPE_11__ {int dropped_frames; void* attempt_framedrops; } ;
struct priv {int coverart_returned; scalar_t__ codec; struct mp_frame decoded_coverart; TYPE_3__* header; TYPE_4__* f; int /*<<< orphan*/  packet; int /*<<< orphan*/  end; int /*<<< orphan*/  start; TYPE_6__ public; struct demux_packet* new_segment; scalar_t__ packets_without_output; TYPE_2__* decoder; } ;
struct mp_pin {int dummy; } ;
struct demux_packet {scalar_t__ codec; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_10__ {struct mp_pin** ppins; } ;
struct TYPE_9__ {scalar_t__ attached_picture; } ;
struct TYPE_8__ {TYPE_1__* f; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_FRAME (int /*<<< orphan*/ ,struct demux_packet*) ; 
 void* MPMAX (int /*<<< orphan*/ ,scalar_t__) ; 
 struct mp_frame MP_EOF_FRAME ; 
 int /*<<< orphan*/  MP_FRAME_PACKET ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  mp_decoder_wrapper_reinit (TYPE_6__*) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (TYPE_4__*) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_progress (TYPE_4__*) ; 
 struct mp_frame mp_frame_ref (struct mp_frame) ; 
 int /*<<< orphan*/  mp_pin_in_needs_data (struct mp_pin*) ; 
 int /*<<< orphan*/  mp_pin_in_write (struct mp_pin*,struct mp_frame) ; 
 struct mp_frame mp_pin_out_read (int /*<<< orphan*/ ) ; 
 int process_decoded_frame (struct priv*,struct mp_frame*) ; 
 int /*<<< orphan*/  reset_decoder (struct priv*) ; 

__attribute__((used)) static void read_frame(struct priv *p)
{
    struct mp_pin *pin = p->f->ppins[0];

    if (!p->decoder || !mp_pin_in_needs_data(pin))
        return;

    if (p->decoded_coverart.type) {
        if (p->coverart_returned == 0) {
            mp_pin_in_write(pin, mp_frame_ref(p->decoded_coverart));
            p->coverart_returned = 1;
        } else if (p->coverart_returned == 1) {
            mp_pin_in_write(pin, MP_EOF_FRAME);
            p->coverart_returned = 2;
        }
        return;
    }

    struct mp_frame frame = mp_pin_out_read(p->decoder->f->pins[1]);
    if (!frame.type)
        return;

    if (p->public.attempt_framedrops) {
        int dropped = MPMAX(0, p->packets_without_output - 1);
        p->public.attempt_framedrops =
            MPMAX(0, p->public.attempt_framedrops - dropped);
        p->public.dropped_frames += dropped;
    }
    p->packets_without_output = 0;

    bool segment_ended = process_decoded_frame(p, &frame);

    // If there's a new segment, start it as soon as we're drained/finished.
    if (segment_ended && p->new_segment) {
        struct demux_packet *new_segment = p->new_segment;
        p->new_segment = NULL;

        reset_decoder(p);

        if (p->codec != new_segment->codec) {
            p->codec = new_segment->codec;
            if (!mp_decoder_wrapper_reinit(&p->public))
                mp_filter_internal_mark_failed(p->f);
        }

        p->start = new_segment->start;
        p->end = new_segment->end;

        p->packet = MAKE_FRAME(MP_FRAME_PACKET, new_segment);
        mp_filter_internal_mark_progress(p->f);
    }

    if (!frame.type) {
        mp_filter_internal_mark_progress(p->f); // make it retry
        return;
    }

    if (p->header->attached_picture && frame.type == MP_FRAME_VIDEO) {
        p->decoded_coverart = mp_frame_ref(frame);
        p->coverart_returned = 1;
    }

    mp_pin_in_write(pin, frame);
}