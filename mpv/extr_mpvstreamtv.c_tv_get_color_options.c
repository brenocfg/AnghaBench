#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  priv; TYPE_2__* functions; } ;
typedef  TYPE_1__ tvi_handle_t ;
struct TYPE_6__ {int (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_2__ tvi_functions_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (TYPE_1__*,char*,int) ; 
 int TVI_CONTROL_UNKNOWN ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_BRIGHTNESS ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_CONTRAST ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_HUE ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_SATURATION ; 
#define  TV_COLOR_BRIGHTNESS 131 
#define  TV_COLOR_CONTRAST 130 
#define  TV_COLOR_HUE 129 
#define  TV_COLOR_SATURATION 128 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int tv_get_color_options(tvi_handle_t *tvh, int opt, int* value)
{
    const tvi_functions_t *funcs = tvh->functions;

    switch(opt)
    {
        case TV_COLOR_BRIGHTNESS:
            return funcs->control(tvh->priv, TVI_CONTROL_VID_GET_BRIGHTNESS, value);
        case TV_COLOR_HUE:
            return funcs->control(tvh->priv, TVI_CONTROL_VID_GET_HUE, value);
        case TV_COLOR_SATURATION:
            return funcs->control(tvh->priv, TVI_CONTROL_VID_GET_SATURATION, value);
        case TV_COLOR_CONTRAST:
            return funcs->control(tvh->priv, TVI_CONTROL_VID_GET_CONTRAST, value);
        default:
            MP_WARN(tvh, "Unknown color option (%d) specified!\n", opt);
    }

    return TVI_CONTROL_UNKNOWN;
}