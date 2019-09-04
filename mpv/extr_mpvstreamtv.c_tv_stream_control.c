#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tvi_handle_t ;

/* Variables and functions */
#define  STREAM_CTRL_GET_TV_COLORS 137 
#define  STREAM_CTRL_GET_TV_FREQ 136 
#define  STREAM_CTRL_SET_TV_COLORS 135 
#define  STREAM_CTRL_SET_TV_FREQ 134 
#define  STREAM_CTRL_TV_LAST_CHAN 133 
#define  STREAM_CTRL_TV_SET_CHAN 132 
#define  STREAM_CTRL_TV_SET_NORM 131 
#define  STREAM_CTRL_TV_SET_SCAN 130 
#define  STREAM_CTRL_TV_STEP_CHAN 129 
#define  STREAM_CTRL_TV_STEP_NORM 128 
 int STREAM_OK ; 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  TV_CHANNEL_HIGHER ; 
 int /*<<< orphan*/  TV_CHANNEL_LOWER ; 
 int /*<<< orphan*/  tv_get_color_options (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  tv_get_freq (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  tv_last_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tv_set_channel (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tv_set_color_options (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tv_set_freq (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  tv_set_norm (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tv_start_scan (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tv_step_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_step_norm (int /*<<< orphan*/ *) ; 

int tv_stream_control(tvi_handle_t *tvh, int cmd, void *arg)
{
    switch (cmd) {
    case STREAM_CTRL_TV_SET_SCAN:
        tv_start_scan(tvh, *(int *)arg);
        return STREAM_OK;
    case STREAM_CTRL_SET_TV_FREQ:
        tv_set_freq(tvh, *(float *)arg * 16.0f);
        return STREAM_OK;
    case STREAM_CTRL_GET_TV_FREQ: {
        unsigned long tmp = 0;
        tv_get_freq(tvh, &tmp);
        *(float *)arg = tmp / 16.0f;
        return STREAM_OK;
    }
    case STREAM_CTRL_SET_TV_COLORS:
        tv_set_color_options(tvh, ((int *)arg)[0], ((int *)arg)[1]);
        return STREAM_OK;
    case STREAM_CTRL_GET_TV_COLORS:
        tv_get_color_options(tvh, ((int *)arg)[0], &((int *)arg)[1]);
        return STREAM_OK;
    case STREAM_CTRL_TV_SET_NORM:
        tv_set_norm(tvh, (char *)arg);
        return STREAM_OK;
    case STREAM_CTRL_TV_STEP_NORM:
        tv_step_norm(tvh);
        return STREAM_OK;
    case STREAM_CTRL_TV_SET_CHAN:
        tv_set_channel(tvh, (char *)arg);
        return STREAM_OK;
    case STREAM_CTRL_TV_STEP_CHAN:
        if (*(int *)arg >= 0) {
            tv_step_channel(tvh, TV_CHANNEL_HIGHER);
        } else {
            tv_step_channel(tvh, TV_CHANNEL_LOWER);
        }
        return STREAM_OK;
    case STREAM_CTRL_TV_LAST_CHAN:
        tv_last_channel(tvh);
        return STREAM_OK;
    }
    return STREAM_UNSUPPORTED;
}