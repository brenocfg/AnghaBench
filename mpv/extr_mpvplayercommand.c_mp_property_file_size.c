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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  demuxer; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_OK ; 
 int M_PROPERTY_PRINT ; 
 int M_PROPERTY_UNAVAILABLE ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_SIZE ; 
 int demux_stream_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* format_file_size (int /*<<< orphan*/ ) ; 
 int m_property_int64_ro (int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_file_size(void *ctx, struct m_property *prop,
                                 int action, void *arg)
{
    MPContext *mpctx = ctx;
    if (!mpctx->demuxer)
        return M_PROPERTY_UNAVAILABLE;

    int64_t size;
    if (demux_stream_control(mpctx->demuxer, STREAM_CTRL_GET_SIZE, &size) < 1)
        return M_PROPERTY_UNAVAILABLE;

    if (action == M_PROPERTY_PRINT) {
        *(char **)arg = format_file_size(size);
        return M_PROPERTY_OK;
    }
    return m_property_int64_ro(action, arg, size);
}