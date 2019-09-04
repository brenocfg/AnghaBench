#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct ra_tex* tex; } ;
struct TYPE_9__ {int /*<<< orphan*/  type; int /*<<< orphan*/  binding; } ;
struct sc_uniform {char const* glsl_type; TYPE_5__ v; TYPE_4__ input; } ;
struct TYPE_7__ {int dimensions; TYPE_1__* format; scalar_t__ external_oes; scalar_t__ non_normalized; } ;
struct ra_tex {TYPE_2__ params; } ;
struct gl_shader_cache {TYPE_3__* ra; } ;
struct TYPE_8__ {scalar_t__ glsl_es; } ;
struct TYPE_6__ {scalar_t__ ctype; } ;

/* Variables and functions */
 scalar_t__ RA_CTYPE_UINT ; 
 int /*<<< orphan*/  RA_VARTYPE_TEX ; 
 struct sc_uniform* find_uniform (struct gl_shader_cache*,char*) ; 
 int /*<<< orphan*/  gl_sc_next_binding (struct gl_shader_cache*,int /*<<< orphan*/ ) ; 

void gl_sc_uniform_texture(struct gl_shader_cache *sc, char *name,
                           struct ra_tex *tex)
{
    const char *glsl_type = "sampler2D";
    if (tex->params.dimensions == 1) {
        glsl_type = "sampler1D";
    } else if (tex->params.dimensions == 3) {
        glsl_type = "sampler3D";
    } else if (tex->params.non_normalized) {
        glsl_type = "sampler2DRect";
    } else if (tex->params.external_oes) {
        glsl_type = "samplerExternalOES";
    } else if (tex->params.format->ctype == RA_CTYPE_UINT) {
        glsl_type = sc->ra->glsl_es ? "highp usampler2D" : "usampler2D";
    }

    struct sc_uniform *u = find_uniform(sc, name);
    u->input.type = RA_VARTYPE_TEX;
    u->glsl_type = glsl_type;
    u->input.binding = gl_sc_next_binding(sc, u->input.type);
    u->v.tex = tex;
}