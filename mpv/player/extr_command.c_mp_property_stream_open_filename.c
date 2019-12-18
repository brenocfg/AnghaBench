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
struct TYPE_2__ {int /*<<< orphan*/  stream_open_filename; int /*<<< orphan*/  demuxer; int /*<<< orphan*/  playing; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_ERROR ; 
#define  M_PROPERTY_GET 130 
#define  M_PROPERTY_GET_TYPE 129 
 int M_PROPERTY_NOT_IMPLEMENTED ; 
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_SET 128 
 int M_PROPERTY_UNAVAILABLE ; 
 int m_property_strdup_ro (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_strdup (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mp_property_stream_open_filename(void *ctx, struct m_property *prop,
                                            int action, void *arg)
{
    MPContext *mpctx = ctx;
    if (!mpctx->stream_open_filename || !mpctx->playing)
        return M_PROPERTY_UNAVAILABLE;
    switch (action) {
    case M_PROPERTY_SET: {
        if (mpctx->demuxer)
            return M_PROPERTY_ERROR;
        mpctx->stream_open_filename =
            talloc_strdup(mpctx->stream_open_filename, *(char **)arg);
        return M_PROPERTY_OK;
    }
    case M_PROPERTY_GET_TYPE:
    case M_PROPERTY_GET:
        return m_property_strdup_ro(action, arg, mpctx->stream_open_filename);
    }
    return M_PROPERTY_NOT_IMPLEMENTED;
}