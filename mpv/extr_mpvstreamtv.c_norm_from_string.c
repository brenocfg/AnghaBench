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
struct TYPE_6__ {int (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ;} ;
typedef  TYPE_2__ tvi_functions_t ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (TYPE_1__*,char*,char*,char*) ; 
 int /*<<< orphan*/  TVI_CONTROL_SPC_GET_NORMID ; 
 int TVI_CONTROL_TRUE ; 
 int TVI_CONTROL_UNKNOWN ; 
 int TV_NORM_NTSC ; 
 int TV_NORM_NTSCJP ; 
 int TV_NORM_PAL ; 
 int TV_NORM_PALM ; 
 int TV_NORM_PALN ; 
 int TV_NORM_PALNC ; 
 int TV_NORM_SECAM ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int norm_from_string(tvi_handle_t *tvh, char* norm)
{
    const tvi_functions_t *funcs = tvh->functions;
    char str[20];
    int ret;

    strncpy(str, norm, sizeof(str)-1);
    str[sizeof(str)-1] = '\0';
    ret=funcs->control(tvh->priv, TVI_CONTROL_SPC_GET_NORMID, str);

    if (ret == TVI_CONTROL_TRUE) {
        int *v = (int *)str;
        return *v;
    }

    if(ret!=TVI_CONTROL_UNKNOWN)
    {
        MP_WARN(tvh, "tv.c: norm_from_string(%s): Bogus norm parameter, setting %s.\n", norm,"default");
        return 0;
    }

    if (!strcasecmp(norm, "pal"))
        return TV_NORM_PAL;
    else if (!strcasecmp(norm, "ntsc"))
        return TV_NORM_NTSC;
    else if (!strcasecmp(norm, "secam"))
        return TV_NORM_SECAM;
    else if (!strcasecmp(norm, "palnc"))
        return TV_NORM_PALNC;
    else if (!strcasecmp(norm, "palm"))
        return TV_NORM_PALM;
    else if (!strcasecmp(norm, "paln"))
        return TV_NORM_PALN;
    else if (!strcasecmp(norm, "ntscjp"))
        return TV_NORM_NTSCJP;
    else {
        MP_WARN(tvh, "tv.c: norm_from_string(%s): Bogus norm parameter, setting %s.\n", norm, "PAL");
        return TV_NORM_PAL;
    }
}