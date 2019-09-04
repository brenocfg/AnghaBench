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
struct TYPE_3__ {int width; int height; } ;
typedef  TYPE_1__ priv_t ;

/* Variables and functions */
 int MP_FOURCC_YV12 ; 
 int TVI_CONTROL_FALSE ; 
#define  TVI_CONTROL_IS_VIDEO 137 
 int TVI_CONTROL_TRUE ; 
#define  TVI_CONTROL_TUN_SET_NORM 136 
 int TVI_CONTROL_UNKNOWN ; 
#define  TVI_CONTROL_VID_CHK_HEIGHT 135 
#define  TVI_CONTROL_VID_CHK_WIDTH 134 
#define  TVI_CONTROL_VID_GET_FORMAT 133 
#define  TVI_CONTROL_VID_GET_HEIGHT 132 
#define  TVI_CONTROL_VID_GET_WIDTH 131 
#define  TVI_CONTROL_VID_SET_FORMAT 130 
#define  TVI_CONTROL_VID_SET_HEIGHT 129 
#define  TVI_CONTROL_VID_SET_WIDTH 128 

__attribute__((used)) static int do_control(priv_t *priv, int cmd, void *arg)
{
    switch(cmd)
    {
        case TVI_CONTROL_IS_VIDEO:
            return TVI_CONTROL_TRUE;
        case TVI_CONTROL_VID_GET_FORMAT:
            *(int *)arg = MP_FOURCC_YV12;
            return TVI_CONTROL_TRUE;
        case TVI_CONTROL_VID_SET_FORMAT:
        {
//          int req_fmt = *(int *)arg;
            int req_fmt = *(int *)arg;
            if (req_fmt != MP_FOURCC_YV12)
                return TVI_CONTROL_FALSE;
            return TVI_CONTROL_TRUE;
        }
        case TVI_CONTROL_VID_SET_WIDTH:
            priv->width = *(int *)arg;
            return TVI_CONTROL_TRUE;
        case TVI_CONTROL_VID_GET_WIDTH:
            *(int *)arg = priv->width;
            return TVI_CONTROL_TRUE;
        case TVI_CONTROL_VID_SET_HEIGHT:
            priv->height = *(int *)arg;
            return TVI_CONTROL_TRUE;
        case TVI_CONTROL_VID_GET_HEIGHT:
            *(int *)arg = priv->height;
            return TVI_CONTROL_TRUE;
        case TVI_CONTROL_VID_CHK_WIDTH:
        case TVI_CONTROL_VID_CHK_HEIGHT:
            return TVI_CONTROL_TRUE;
        case TVI_CONTROL_TUN_SET_NORM:
            return TVI_CONTROL_TRUE;
    }
    return TVI_CONTROL_UNKNOWN;
}