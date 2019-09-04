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
struct mp_image_params {int dummy; } ;
struct sd_lavc_priv {struct mp_image_params video_params; } ;
struct sd {struct sd_lavc_priv* priv; } ;
typedef  enum sd_ctrl { ____Placeholder_sd_ctrl } sd_ctrl ;

/* Variables and functions */
 int CONTROL_OK ; 
 int CONTROL_UNKNOWN ; 
 double MP_NOPTS_VALUE ; 
#define  SD_CTRL_SET_VIDEO_PARAMS 129 
#define  SD_CTRL_SUB_STEP 128 
 double step_sub (struct sd*,double,double) ; 

__attribute__((used)) static int control(struct sd *sd, enum sd_ctrl cmd, void *arg)
{
    struct sd_lavc_priv *priv = sd->priv;
    switch (cmd) {
    case SD_CTRL_SUB_STEP: {
        double *a = arg;
        double res = step_sub(sd, a[0], a[1]);
        if (res == MP_NOPTS_VALUE)
            return false;
        a[0] = res;
        return true;
    }
    case SD_CTRL_SET_VIDEO_PARAMS:
        priv->video_params = *(struct mp_image_params *)arg;
        return CONTROL_OK;
    default:
        return CONTROL_UNKNOWN;
    }
}