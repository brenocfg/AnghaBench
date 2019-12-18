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
struct priv {scalar_t__ vo_dev; scalar_t__ device_ctx; scalar_t__ video_dev; scalar_t__ video_ctx; int /*<<< orphan*/  pool; int /*<<< orphan*/  queue; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11DeviceContext_Release (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11Device_Release (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11VideoContext_Release (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11VideoDevice_Release (scalar_t__) ; 
 int /*<<< orphan*/  destroy_video_proc (struct mp_filter*) ; 
 int /*<<< orphan*/  flush_frames (struct mp_filter*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uninit(struct mp_filter *vf)
{
    struct priv *p = vf->priv;

    destroy_video_proc(vf);

    flush_frames(vf);
    talloc_free(p->queue);
    talloc_free(p->pool);

    if (p->video_ctx)
        ID3D11VideoContext_Release(p->video_ctx);

    if (p->video_dev)
        ID3D11VideoDevice_Release(p->video_dev);

    if (p->device_ctx)
        ID3D11DeviceContext_Release(p->device_ctx);

    if (p->vo_dev)
        ID3D11Device_Release(p->vo_dev);
}