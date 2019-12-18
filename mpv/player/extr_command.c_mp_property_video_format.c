#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct track {TYPE_2__* stream; } ;
struct m_property {int dummy; } ;
struct TYPE_6__ {struct track*** current_track; } ;
struct TYPE_5__ {TYPE_1__* codec; } ;
struct TYPE_4__ {char* codec; } ;
typedef  TYPE_3__ MPContext ;

/* Variables and functions */
 size_t STREAM_VIDEO ; 
 int m_property_strdup_ro (int,void*,char const*) ; 

__attribute__((used)) static int mp_property_video_format(void *ctx, struct m_property *prop,
                                    int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct track *track = mpctx->current_track[0][STREAM_VIDEO];
    const char *c = track && track->stream ? track->stream->codec->codec : NULL;
    return m_property_strdup_ro(action, arg, c);
}