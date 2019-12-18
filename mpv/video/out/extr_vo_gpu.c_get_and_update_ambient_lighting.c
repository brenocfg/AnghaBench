#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpu_priv {int /*<<< orphan*/  renderer; int /*<<< orphan*/  events; TYPE_2__* ctx; } ;
struct TYPE_4__ {TYPE_1__* fns; } ;
struct TYPE_3__ {int (* control ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct gpu_priv*,char*) ; 
 int /*<<< orphan*/  VOCTRL_GET_AMBIENT_LUX ; 
 int VO_TRUE ; 
 scalar_t__ gl_video_gamma_auto_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_video_set_ambient_lux (int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void get_and_update_ambient_lighting(struct gpu_priv *p)
{
    int lux;
    int r = p->ctx->fns->control(p->ctx, &p->events, VOCTRL_GET_AMBIENT_LUX, &lux);
    if (r == VO_TRUE) {
        gl_video_set_ambient_lux(p->renderer, lux);
    }
    if (r != VO_TRUE && gl_video_gamma_auto_enabled(p->renderer)) {
        MP_ERR(p, "gamma_auto option provided, but querying for ambient"
                  " lighting is not supported on this platform\n");
    }
}