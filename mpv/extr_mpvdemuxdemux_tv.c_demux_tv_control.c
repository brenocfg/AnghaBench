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
typedef  int /*<<< orphan*/  tvi_handle_t ;
struct demux_ctrl_stream_ctrl {int /*<<< orphan*/  arg; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  res; } ;
struct TYPE_3__ {scalar_t__ priv; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int CONTROL_OK ; 
 int CONTROL_UNKNOWN ; 
 int DEMUXER_CTRL_STREAM_CTRL ; 
 int /*<<< orphan*/  tv_stream_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int demux_tv_control(demuxer_t *demuxer, int cmd, void *arg)
{
    tvi_handle_t *tvh=(tvi_handle_t*)(demuxer->priv);
    if (cmd != DEMUXER_CTRL_STREAM_CTRL)
        return CONTROL_UNKNOWN;
    struct demux_ctrl_stream_ctrl *ctrl = arg;
    ctrl->res = tv_stream_control(tvh, ctrl->ctrl, ctrl->arg);
    return CONTROL_OK;
}