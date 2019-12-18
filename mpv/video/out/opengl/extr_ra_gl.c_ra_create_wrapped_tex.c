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
struct ra_tex_params {int dummy; } ;
struct ra_tex_gl {int /*<<< orphan*/  texture; } ;
struct ra_tex {struct ra_tex_gl* priv; } ;
struct ra {int dummy; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 struct ra_tex* gl_tex_create_blank (struct ra*,struct ra_tex_params const*) ; 

struct ra_tex *ra_create_wrapped_tex(struct ra *ra,
                                     const struct ra_tex_params *params,
                                     GLuint gl_texture)
{
    struct ra_tex *tex = gl_tex_create_blank(ra, params);
    if (!tex)
        return NULL;
    struct ra_tex_gl *tex_gl = tex->priv;
    tex_gl->texture = gl_texture;
    return tex;
}