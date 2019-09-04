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
struct m_property {int dummy; } ;
struct demuxer {scalar_t__ filepos; } ;
struct TYPE_2__ {struct demuxer* demuxer; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 int m_property_int64_ro (int,void*,scalar_t__) ; 

__attribute__((used)) static int mp_property_stream_pos(void *ctx, struct m_property *prop,
                                  int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct demuxer *demuxer = mpctx->demuxer;
    if (!demuxer || demuxer->filepos < 0)
        return M_PROPERTY_UNAVAILABLE;
    return m_property_int64_ro(action, arg, demuxer->filepos);
}