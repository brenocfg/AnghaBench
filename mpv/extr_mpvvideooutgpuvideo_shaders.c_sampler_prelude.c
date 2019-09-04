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
struct gl_shader_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLSLF (char*,...) ; 

void sampler_prelude(struct gl_shader_cache *sc, int tex_num)
{
    GLSLF("#undef tex\n");
    GLSLF("#undef texmap\n");
    GLSLF("#define tex texture%d\n", tex_num);
    GLSLF("#define texmap texmap%d\n", tex_num);
    GLSLF("vec2 pos = texcoord%d;\n", tex_num);
    GLSLF("vec2 size = texture_size%d;\n", tex_num);
    GLSLF("vec2 pt = pixel_size%d;\n", tex_num);
}