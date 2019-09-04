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
struct demuxer {int dummy; } ;
struct MPContext {scalar_t__ playback_pts; scalar_t__ last_seek_pts; struct demuxer* demuxer; } ;

/* Variables and functions */
 scalar_t__ MP_NOPTS_VALUE ; 

double get_current_time(struct MPContext *mpctx)
{
    struct demuxer *demuxer = mpctx->demuxer;
    if (demuxer) {
        if (mpctx->playback_pts != MP_NOPTS_VALUE)
            return mpctx->playback_pts;
        if (mpctx->last_seek_pts != MP_NOPTS_VALUE)
            return mpctx->last_seek_pts;
    }
    return MP_NOPTS_VALUE;
}