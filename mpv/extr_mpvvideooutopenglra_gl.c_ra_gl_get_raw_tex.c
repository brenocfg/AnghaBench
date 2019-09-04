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
struct ra_tex_gl {int /*<<< orphan*/  target; int /*<<< orphan*/  texture; } ;
struct ra_tex {struct ra_tex_gl* priv; } ;
struct ra {int dummy; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */

void ra_gl_get_raw_tex(struct ra *ra, struct ra_tex *tex,
                       GLuint *out_texture, GLenum *out_target)
{
    struct ra_tex_gl *tex_gl = tex->priv;
    *out_texture = tex_gl->texture;
    *out_target = tex_gl->target;
}