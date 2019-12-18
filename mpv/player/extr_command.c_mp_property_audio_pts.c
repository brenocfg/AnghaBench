#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_3__ {scalar_t__ audio_status; int /*<<< orphan*/  playback_initialized; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 scalar_t__ STATUS_EOF ; 
 scalar_t__ STATUS_PLAYING ; 
 int /*<<< orphan*/  playing_audio_pts (TYPE_1__*) ; 
 int property_time (int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_audio_pts(void *ctx, struct m_property *prop,
                                int action, void *arg)
{
    MPContext *mpctx = ctx;
    if (!mpctx->playback_initialized || mpctx->audio_status < STATUS_PLAYING ||
        mpctx->audio_status >= STATUS_EOF)
        return M_PROPERTY_UNAVAILABLE;

    return property_time(action, arg, playing_audio_pts(mpctx));
}