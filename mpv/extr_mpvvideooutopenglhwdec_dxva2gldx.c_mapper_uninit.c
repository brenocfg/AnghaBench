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
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; struct priv* priv; } ;
struct priv {int /*<<< orphan*/ * rtarget; scalar_t__ texture; scalar_t__ rtarget_h; scalar_t__ device_h; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DeleteTextures ) (int,scalar_t__*) ;int /*<<< orphan*/  (* DXUnregisterObjectNV ) (scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* DXUnlockObjectsNV ) (scalar_t__,int,scalar_t__*) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DSurface9_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec_mapper*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_LastError_to_str () ; 
 TYPE_1__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int,scalar_t__*) ; 

__attribute__((used)) static void mapper_uninit(struct ra_hwdec_mapper *mapper)
{
    struct priv *p = mapper->priv;
    GL *gl = ra_gl_get(mapper->ra);

    if (p->rtarget_h && p->device_h) {
        if (!gl->DXUnlockObjectsNV(p->device_h, 1, &p->rtarget_h)) {
            MP_ERR(mapper, "Failed unlocking texture for access by OpenGL: %s\n",
                   mp_LastError_to_str());
        }
    }

    if (p->rtarget_h) {
        if (!gl->DXUnregisterObjectNV(p->device_h, p->rtarget_h)) {
            MP_ERR(mapper, "Failed to unregister Direct3D surface with OpenGL: %s\n",
                   mp_LastError_to_str());
        } else {
            p->rtarget_h = 0;
        }
    }

    gl->DeleteTextures(1, &p->texture);
    p->texture = 0;

    if (p->rtarget) {
        IDirect3DSurface9_Release(p->rtarget);
        p->rtarget = NULL;
    }

    ra_tex_free(mapper->ra, &mapper->tex[0]);
}