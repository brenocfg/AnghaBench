#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec_mapper {int /*<<< orphan*/  ra; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  gl_planes; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DeleteTextures ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  MP_MAX_PLANES ; 
 TYPE_1__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mapper_uninit(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;
    GL *gl = ra_gl_get(mapper->ra);

    gl->DeleteTextures(MP_MAX_PLANES, p->gl_planes);
}