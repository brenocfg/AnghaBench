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
struct priv {int vol; int /*<<< orphan*/  hdl; int /*<<< orphan*/  havevol; } ;
struct ao {struct priv* priv; } ;
typedef  enum aocontrol { ____Placeholder_aocontrol } aocontrol ;
struct TYPE_2__ {int left; int right; } ;
typedef  TYPE_1__ ao_control_vol_t ;

/* Variables and functions */
#define  AOCONTROL_GET_VOLUME 129 
#define  AOCONTROL_SET_VOLUME 128 
 int CONTROL_FALSE ; 
 int CONTROL_OK ; 
 int CONTROL_UNKNOWN ; 
 int SIO_MAXVOL ; 
 int /*<<< orphan*/  sio_setvol (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int control(struct ao *ao, enum aocontrol cmd, void *arg)
{
    struct priv *p = ao->priv;
    ao_control_vol_t *vol = arg;

    switch (cmd) {
    case AOCONTROL_GET_VOLUME:
        if (!p->havevol)
            return CONTROL_FALSE;
        vol->left = vol->right = p->vol * 100 / SIO_MAXVOL;
        break;
    case AOCONTROL_SET_VOLUME:
        if (!p->havevol)
            return CONTROL_FALSE;
        sio_setvol(p->hdl, vol->left * SIO_MAXVOL / 100);
        break;
    default:
        return CONTROL_UNKNOWN;
    }
    return CONTROL_OK;
}