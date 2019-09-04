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
struct mp_aframe {int /*<<< orphan*/  av_frame; int /*<<< orphan*/  speed; int /*<<< orphan*/  pts; int /*<<< orphan*/  format; int /*<<< orphan*/  chmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ av_frame_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_aframe_config_copy (struct mp_aframe*,struct mp_aframe*) ; 
 struct mp_aframe* mp_aframe_create () ; 
 scalar_t__ mp_aframe_is_allocated (struct mp_aframe*) ; 

struct mp_aframe *mp_aframe_new_ref(struct mp_aframe *frame)
{
    if (!frame)
        return NULL;

    struct mp_aframe *dst = mp_aframe_create();

    dst->chmap = frame->chmap;
    dst->format = frame->format;
    dst->pts = frame->pts;
    dst->speed = frame->speed;

    if (mp_aframe_is_allocated(frame)) {
        if (av_frame_ref(dst->av_frame, frame->av_frame) < 0)
            abort();
    } else {
        // av_frame_ref() would fail.
        mp_aframe_config_copy(dst, frame);
    }

    return dst;
}