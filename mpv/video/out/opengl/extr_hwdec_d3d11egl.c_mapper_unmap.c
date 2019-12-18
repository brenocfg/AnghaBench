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
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; struct priv* priv; TYPE_1__* owner; } ;
struct priv_owner {int /*<<< orphan*/  egl_display; int /*<<< orphan*/  (* StreamConsumerReleaseKHR ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct priv {scalar_t__ egl_stream; } ;
struct TYPE_2__ {struct priv_owner* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mapper_unmap(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *o = mapper->owner->priv;
    struct priv *p = mapper->priv;

    for (int n = 0; n < 2; n++)
        ra_tex_free(mapper->ra, &mapper->tex[n]);
    if (p->egl_stream)
        o->StreamConsumerReleaseKHR(o->egl_display, p->egl_stream);
}