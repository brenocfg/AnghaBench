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
struct ra_tex_gl {int /*<<< orphan*/  type; int /*<<< orphan*/  format; int /*<<< orphan*/  fbo; } ;
struct ra_tex_download_params {int /*<<< orphan*/  stride; int /*<<< orphan*/  dst; struct ra_tex* tex; } ;
struct TYPE_2__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct ra_tex {TYPE_1__ params; struct ra_tex_gl* priv; } ;
struct ra {int dummy; } ;
typedef  int /*<<< orphan*/  GL ;

/* Variables and functions */
 int gl_read_fbo_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ra_gl_get (struct ra*) ; 

__attribute__((used)) static bool gl_tex_download(struct ra *ra, struct ra_tex_download_params *params)
{
    GL *gl = ra_gl_get(ra);
    struct ra_tex *tex = params->tex;
    struct ra_tex_gl *tex_gl = tex->priv;
    if (!tex_gl->fbo)
        return false;
    return gl_read_fbo_contents(gl, tex_gl->fbo, 1, tex_gl->format, tex_gl->type,
                                tex->params.w, tex->params.h, params->dst,
                                params->stride);
}