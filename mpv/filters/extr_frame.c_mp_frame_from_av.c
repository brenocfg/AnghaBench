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
struct mp_frame {int member_0; size_t type; int /*<<< orphan*/  data; } ;
struct AVRational {int dummy; } ;
struct AVFrame {int /*<<< orphan*/  pts; } ;
typedef  enum mp_frame_type { ____Placeholder_mp_frame_type } mp_frame_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* from_av_ref ) (struct AVFrame*) ;} ;

/* Variables and functions */
 struct mp_frame MP_NO_FRAME ; 
 TYPE_1__* frame_handlers ; 
 int /*<<< orphan*/  mp_frame_set_pts (struct mp_frame,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pts_from_av (int /*<<< orphan*/ ,struct AVRational*) ; 
 int /*<<< orphan*/  stub1 (struct AVFrame*) ; 

struct mp_frame mp_frame_from_av(enum mp_frame_type type, struct AVFrame *frame,
                                 struct AVRational *tb)
{
    struct mp_frame res = {type};

    if (!frame_handlers[res.type].from_av_ref)
        return MP_NO_FRAME;

    res.data = frame_handlers[res.type].from_av_ref(frame);
    if (!res.data)
        return MP_NO_FRAME;

    mp_frame_set_pts(res, mp_pts_from_av(frame->pts, tb));
    return res;
}