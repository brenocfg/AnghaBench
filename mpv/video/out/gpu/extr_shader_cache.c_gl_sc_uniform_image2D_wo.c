#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct ra_tex* tex; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  binding; } ;
struct sc_uniform {char* glsl_type; TYPE_2__ v; TYPE_1__ input; } ;
struct ra_tex {int dummy; } ;
struct gl_shader_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RA_VARTYPE_IMG_W ; 
 struct sc_uniform* find_uniform (struct gl_shader_cache*,char const*) ; 
 int /*<<< orphan*/  gl_sc_enable_extension (struct gl_shader_cache*,char*) ; 
 int /*<<< orphan*/  gl_sc_next_binding (struct gl_shader_cache*,int /*<<< orphan*/ ) ; 

void gl_sc_uniform_image2D_wo(struct gl_shader_cache *sc, const char *name,
                              struct ra_tex *tex)
{
    gl_sc_enable_extension(sc, "GL_ARB_shader_image_load_store");

    struct sc_uniform *u = find_uniform(sc, name);
    u->input.type = RA_VARTYPE_IMG_W;
    u->glsl_type = "writeonly image2D";
    u->input.binding = gl_sc_next_binding(sc, u->input.type);
    u->v.tex = tex;
}