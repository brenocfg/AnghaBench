#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct m_option {int min; int max; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct demuxer {int /*<<< orphan*/  extended_ctrls; } ;
struct TYPE_5__ {struct demuxer* demuxer; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_RANGE ; 
 int /*<<< orphan*/  CONF_TYPE_INT ; 
 int /*<<< orphan*/  DEMUXER_CTRL_RESYNC ; 
 int M_PROPERTY_ERROR ; 
#define  M_PROPERTY_GET 131 
#define  M_PROPERTY_GET_TYPE 130 
 int M_PROPERTY_NOT_IMPLEMENTED ; 
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_PRINT 129 
#define  M_PROPERTY_SET 128 
 int M_PROPERTY_UNAVAILABLE ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_ANGLE ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_NUM_ANGLES ; 
 int /*<<< orphan*/  STREAM_CTRL_SET_ANGLE ; 
 int STREAM_OK ; 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  demux_control (struct demuxer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  demux_flush (struct demuxer*) ; 
 int demux_stream_control (struct demuxer*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mp_wakeup_core (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_audio_state (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_video_state (TYPE_1__*) ; 
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static int mp_property_angle(void *ctx, struct m_property *prop,
                             int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct demuxer *demuxer = mpctx->demuxer;
    if (!demuxer || !demuxer->extended_ctrls)
        return M_PROPERTY_UNAVAILABLE;

    int ris, angles = -1, angle = 1;

    ris = demux_stream_control(demuxer, STREAM_CTRL_GET_NUM_ANGLES, &angles);
    if (ris == STREAM_UNSUPPORTED)
        return M_PROPERTY_UNAVAILABLE;

    ris = demux_stream_control(demuxer, STREAM_CTRL_GET_ANGLE, &angle);
    if (ris == STREAM_UNSUPPORTED)
        return -1;

    if (angle < 0 || angles <= 1)
        return M_PROPERTY_UNAVAILABLE;

    switch (action) {
    case M_PROPERTY_GET:
        *(int *) arg = angle;
        return M_PROPERTY_OK;
    case M_PROPERTY_PRINT: {
        *(char **) arg = talloc_asprintf(NULL, "%d/%d", angle, angles);
        return M_PROPERTY_OK;
    }
    case M_PROPERTY_SET:
        angle = *(int *)arg;
        if (angle < 0 || angle > angles)
            return M_PROPERTY_ERROR;

        demux_flush(demuxer);
        ris = demux_stream_control(demuxer, STREAM_CTRL_SET_ANGLE, &angle);
        if (ris == STREAM_OK) {
            demux_control(demuxer, DEMUXER_CTRL_RESYNC, NULL);
            demux_flush(demuxer);
        }

        reset_audio_state(mpctx);
        reset_video_state(mpctx);
        mp_wakeup_core(mpctx);

        return ris == STREAM_OK ? M_PROPERTY_OK : M_PROPERTY_ERROR;
    case M_PROPERTY_GET_TYPE: {
        struct m_option opt = {
            .type = CONF_TYPE_INT,
            .flags = CONF_RANGE,
            .min = 1,
            .max = angles,
        };
        *(struct m_option *)arg = opt;
        return M_PROPERTY_OK;
    }
    }
    return M_PROPERTY_NOT_IMPLEMENTED;
}