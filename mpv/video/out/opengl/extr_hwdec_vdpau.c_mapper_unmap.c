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
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; struct priv* priv; } ;
struct priv {int mapped; scalar_t__ vdpgl_surface; scalar_t__ direct_mode; TYPE_1__* gl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* VDPAUUnregisterSurfaceNV ) (scalar_t__) ;int /*<<< orphan*/  (* VDPAUUnmapSurfacesNV ) (int,scalar_t__*) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 

__attribute__((used)) static void mapper_unmap(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;
    GL *gl = p->gl;

    for (int n = 0; n < 4; n++)
        ra_tex_free(mapper->ra, &mapper->tex[n]);

    if (p->mapped) {
        gl->VDPAUUnmapSurfacesNV(1, &p->vdpgl_surface);
        if (p->direct_mode) {
            gl->VDPAUUnregisterSurfaceNV(p->vdpgl_surface);
            p->vdpgl_surface = 0;
        }
    }
    p->mapped = false;
}