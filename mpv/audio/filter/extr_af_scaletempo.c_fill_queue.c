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
typedef  int /*<<< orphan*/  uint8_t ;
struct priv {int bytes_per_frame; scalar_t__ bytes_to_slide; scalar_t__ bytes_queued; int buf_queue; int bytes_queue; scalar_t__ in; } ;

/* Variables and functions */
 int MPMIN (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int,int,int) ; 
 int /*<<< orphan*/ ** mp_aframe_get_data_ro (scalar_t__) ; 
 int mp_aframe_get_size (scalar_t__) ; 
 int /*<<< orphan*/  mp_aframe_skip_samples (scalar_t__,int) ; 

__attribute__((used)) static bool fill_queue(struct priv *s)
{
    int bytes_in = s->in ? mp_aframe_get_size(s->in) * s->bytes_per_frame : 0;
    int offset = 0;

    if (s->bytes_to_slide > 0) {
        if (s->bytes_to_slide < s->bytes_queued) {
            int bytes_move = s->bytes_queued - s->bytes_to_slide;
            memmove(s->buf_queue, s->buf_queue + s->bytes_to_slide, bytes_move);
            s->bytes_to_slide = 0;
            s->bytes_queued = bytes_move;
        } else {
            int bytes_skip;
            s->bytes_to_slide -= s->bytes_queued;
            bytes_skip = MPMIN(s->bytes_to_slide, bytes_in);
            s->bytes_queued = 0;
            s->bytes_to_slide -= bytes_skip;
            offset += bytes_skip;
            bytes_in -= bytes_skip;
        }
    }

    int bytes_needed = s->bytes_queue - s->bytes_queued;
    assert(bytes_needed >= 0);

    int bytes_copy = MPMIN(bytes_needed, bytes_in);
    if (bytes_copy > 0) {
        uint8_t **planes = mp_aframe_get_data_ro(s->in);
        memcpy(s->buf_queue + s->bytes_queued, planes[0] + offset, bytes_copy);
        s->bytes_queued += bytes_copy;
        offset += bytes_copy;
        bytes_needed -= bytes_copy;
    }

    if (s->in)
        mp_aframe_skip_samples(s->in, offset / s->bytes_per_frame);

    return bytes_needed == 0;
}