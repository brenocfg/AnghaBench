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
struct vo {scalar_t__ hwdec_devs; struct gpu_priv* priv; } ;
struct gpu_priv {int /*<<< orphan*/  ctx; int /*<<< orphan*/  renderer; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_video_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwdec_devices_destroy (scalar_t__) ; 
 int /*<<< orphan*/  hwdec_devices_set_loader (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_ctx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct gpu_priv *p = vo->priv;

    gl_video_uninit(p->renderer);
    if (vo->hwdec_devs) {
        hwdec_devices_set_loader(vo->hwdec_devs, NULL, NULL);
        hwdec_devices_destroy(vo->hwdec_devs);
    }
    ra_ctx_destroy(&p->ctx);
}