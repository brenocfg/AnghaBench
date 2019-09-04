#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec_mapper {int /*<<< orphan*/  ra; struct priv* priv; TYPE_1__* owner; } ;
struct priv_owner {int /*<<< orphan*/  egl_display; int /*<<< orphan*/  (* DestroyStreamKHR ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct priv {int /*<<< orphan*/  gl_textures; scalar_t__ egl_stream; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* DeleteTextures ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct priv_owner* priv; } ;
typedef  TYPE_2__ GL ;

/* Variables and functions */
 TYPE_2__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mapper_uninit(struct ra_hwdec_mapper *mapper)
{
    struct priv_owner *o = mapper->owner->priv;
    struct priv *p = mapper->priv;
    GL *gl = ra_gl_get(mapper->ra);

    if (p->egl_stream)
        o->DestroyStreamKHR(o->egl_display, p->egl_stream);
    p->egl_stream = 0;

    gl->DeleteTextures(2, p->gl_textures);
}