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
struct TYPE_3__ {float* f; } ;
struct TYPE_4__ {int dim_v; int dim_m; int /*<<< orphan*/  type; } ;
struct sc_uniform {char* glsl_type; TYPE_1__ v; TYPE_2__ input; } ;
struct gl_shader_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RA_VARTYPE_FLOAT ; 
 struct sc_uniform* find_uniform (struct gl_shader_cache*,char*) ; 
 int /*<<< orphan*/  transpose3x3 (float*) ; 
 int /*<<< orphan*/  update_uniform_params (struct gl_shader_cache*,struct sc_uniform*) ; 

void gl_sc_uniform_mat3(struct gl_shader_cache *sc, char *name,
                        bool transpose, float *v)
{
    struct sc_uniform *u = find_uniform(sc, name);
    u->input.type = RA_VARTYPE_FLOAT;
    u->input.dim_v = 3;
    u->input.dim_m = 3;
    u->glsl_type = "mat3";
    update_uniform_params(sc, u);
    for (int n = 0; n < 9; n++)
        u->v.f[n] = v[n];
    if (transpose)
        transpose3x3(&u->v.f[0]);
}