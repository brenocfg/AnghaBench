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
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ shader_version; } ;
struct wined3d_shader {TYPE_2__ reg_maps; struct wined3d_device* device; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ WINED3D_SHADER_TYPE_COMPUTE ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  shader_glsl_compile_compute_shader (void*,struct wined3d_context*,struct wined3d_shader*) ; 

__attribute__((used)) static void shader_glsl_precompile(void *shader_priv, struct wined3d_shader *shader)
{
    struct wined3d_device *device = shader->device;
    struct wined3d_context *context;

    if (shader->reg_maps.shader_version.type == WINED3D_SHADER_TYPE_COMPUTE)
    {
        context = context_acquire(device, NULL, 0);
        shader_glsl_compile_compute_shader(shader_priv, context, shader);
        context_release(context);
    }
}