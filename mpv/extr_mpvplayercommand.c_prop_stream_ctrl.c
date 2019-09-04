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
struct MPContext {TYPE_1__* demuxer; } ;
struct TYPE_2__ {int /*<<< orphan*/  extended_ctrls; } ;

/* Variables and functions */
 int M_PROPERTY_ERROR ; 
 int M_PROPERTY_OK ; 
 int M_PROPERTY_UNAVAILABLE ; 
#define  STREAM_OK 129 
#define  STREAM_UNSUPPORTED 128 
 int demux_stream_control (TYPE_1__*,int,void*) ; 

__attribute__((used)) static int prop_stream_ctrl(struct MPContext *mpctx, int ctrl, void *arg)
{
    if (!mpctx->demuxer || !mpctx->demuxer->extended_ctrls)
        return M_PROPERTY_UNAVAILABLE;
    int r = demux_stream_control(mpctx->demuxer, ctrl, arg);
    switch (r) {
    case STREAM_OK: return M_PROPERTY_OK;
    case STREAM_UNSUPPORTED: return M_PROPERTY_UNAVAILABLE;
    default: return M_PROPERTY_ERROR;
    }
}