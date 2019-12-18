#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct MPContext {scalar_t__ video_pts; int /*<<< orphan*/  next_frames; TYPE_4__* video_out; TYPE_1__* opts; TYPE_3__* vo_chain; } ;
struct TYPE_8__ {TYPE_2__* driver; } ;
struct TYPE_7__ {scalar_t__ is_sparse; } ;
struct TYPE_6__ {int caps; scalar_t__ untimed; } ;
struct TYPE_5__ {scalar_t__ video_latency_hacks; scalar_t__ untimed; } ;

/* Variables and functions */
 int MPCLAMP (int,int,scalar_t__) ; 
 scalar_t__ MP_ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MP_NOPTS_VALUE ; 
 int VO_CAP_NORETAIN ; 
 int vo_get_num_req_frames (TYPE_4__*) ; 

__attribute__((used)) static int get_req_frames(struct MPContext *mpctx, bool eof)
{
    // On EOF, drain all frames.
    if (eof)
        return 1;

    if (mpctx->video_out->driver->caps & VO_CAP_NORETAIN)
        return 1;

    if (mpctx->vo_chain && mpctx->vo_chain->is_sparse)
        return 1;

    if (mpctx->opts->untimed || mpctx->video_out->driver->untimed)
        return 1;

    // Normally require at least 2 frames, so we can compute a frame duration.
    int min = mpctx->opts->video_latency_hacks ? 1 : 2;

    // On the first frame, output a new frame as quickly as possible.
    if (mpctx->video_pts == MP_NOPTS_VALUE)
        return min;

    int req = vo_get_num_req_frames(mpctx->video_out);
    return MPCLAMP(req, min, MP_ARRAY_SIZE(mpctx->next_frames) - 1);
}