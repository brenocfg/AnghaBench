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
struct ra_renderpass_input {int dim_v; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static const char *vao_glsl_type(const struct ra_renderpass_input *e)
{
    // pretty dumb... too dumb, but works for us
    switch (e->dim_v) {
    case 1: return "float";
    case 2: return "vec2";
    case 3: return "vec3";
    case 4: return "vec4";
    default: abort();
    }
}