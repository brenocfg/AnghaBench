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
struct demuxer {int /*<<< orphan*/  extended_ctrls; } ;
struct TYPE_3__ {struct demuxer* demuxer; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_NUM_TITLES ; 
 int demux_stream_control (struct demuxer*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  get_disc_title_entry ; 
 int m_property_read_list (int,void*,unsigned int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int mp_property_list_disc_titles(void *ctx, struct m_property *prop,
                                        int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct demuxer *demuxer = mpctx->demuxer;
    unsigned int num_titles;
    if (!demuxer || !demuxer->extended_ctrls ||
        demux_stream_control(demuxer, STREAM_CTRL_GET_NUM_TITLES,
                             &num_titles) < 1)
        return M_PROPERTY_UNAVAILABLE;
    return m_property_read_list(action, arg, num_titles,
                                get_disc_title_entry, mpctx);
}