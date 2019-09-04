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
struct demux_ctrl_reader_state {int /*<<< orphan*/  idle; } ;
struct TYPE_2__ {int /*<<< orphan*/  demuxer; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUXER_CTRL_GET_READER_STATE ; 
 int M_PROPERTY_UNAVAILABLE ; 
 int demux_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct demux_ctrl_reader_state*) ; 
 int m_property_flag_ro (int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_demuxer_cache_idle(void *ctx, struct m_property *prop,
                                          int action, void *arg)
{
    MPContext *mpctx = ctx;
    if (!mpctx->demuxer)
        return M_PROPERTY_UNAVAILABLE;

    struct demux_ctrl_reader_state s;
    if (demux_control(mpctx->demuxer, DEMUXER_CTRL_GET_READER_STATE, &s) < 1)
        return M_PROPERTY_UNAVAILABLE;

    return m_property_flag_ro(action, arg, s.idle);
}