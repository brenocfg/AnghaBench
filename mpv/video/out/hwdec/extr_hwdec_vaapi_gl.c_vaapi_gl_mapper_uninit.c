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
struct vaapi_gl_mapper_priv {scalar_t__* gl_textures; } ;
struct ra_hwdec_mapper {int /*<<< orphan*/  ra; struct priv* priv; } ;
struct priv {struct vaapi_gl_mapper_priv* interop_mapper_priv; int /*<<< orphan*/ * tex; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DeleteTextures ) (int,scalar_t__*) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 TYPE_1__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__*) ; 
 int /*<<< orphan*/  talloc_free (struct vaapi_gl_mapper_priv*) ; 

__attribute__((used)) static void vaapi_gl_mapper_uninit(const struct ra_hwdec_mapper *mapper)
{
    struct priv *p_mapper = mapper->priv;
    struct vaapi_gl_mapper_priv *p = p_mapper->interop_mapper_priv;

    if (p) {
        GL *gl = ra_gl_get(mapper->ra);
        gl->DeleteTextures(4, p->gl_textures);
        for (int n = 0; n < 4; n++) {
            p->gl_textures[n] = 0;
            ra_tex_free(mapper->ra, &p_mapper->tex[n]);
        }
        talloc_free(p);
        p_mapper->interop_mapper_priv = NULL;
    }
}