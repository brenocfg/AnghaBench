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
typedef  int uint32_t ;
struct vo {struct priv* priv; } ;
struct priv {double cfg_fps; } ;

/* Variables and functions */
#define  VOCTRL_GET_DISPLAY_FPS 128 
 int VO_NOTIMPL ; 
 int VO_TRUE ; 

__attribute__((used)) static int control(struct vo *vo, uint32_t request, void *data)
{
    struct priv *p = vo->priv;
    switch (request) {
    case VOCTRL_GET_DISPLAY_FPS:
        if (!p->cfg_fps)
            break;
        *(double *)data = p->cfg_fps;
        return VO_TRUE;
    }
    return VO_NOTIMPL;
}