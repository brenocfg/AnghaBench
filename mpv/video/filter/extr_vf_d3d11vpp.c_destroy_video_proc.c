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
struct priv {int /*<<< orphan*/ * vp_enum; int /*<<< orphan*/ * video_proc; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11VideoProcessorEnumerator_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11VideoProcessor_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_video_proc(struct mp_filter *vf)
{
    struct priv *p = vf->priv;

    if (p->video_proc)
        ID3D11VideoProcessor_Release(p->video_proc);
    p->video_proc = NULL;

    if (p->vp_enum)
        ID3D11VideoProcessorEnumerator_Release(p->vp_enum);
    p->vp_enum = NULL;
}