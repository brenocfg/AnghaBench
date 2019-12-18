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
struct wined3d_context {struct glsl_context_data* shader_backend_data; } ;
struct glsl_context_data {int /*<<< orphan*/  vertex_color_clamp; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_FIXED_ONLY_ARB ; 
 int /*<<< orphan*/  TRUE ; 
 struct glsl_context_data* heap_alloc_zero (int) ; 

__attribute__((used)) static BOOL shader_glsl_allocate_context_data(struct wined3d_context *context)
{
    struct glsl_context_data *ctx_data;

    if (!(ctx_data = heap_alloc_zero(sizeof(*ctx_data))))
        return FALSE;
    ctx_data->vertex_color_clamp = GL_FIXED_ONLY_ARB;
    context->shader_backend_data = ctx_data;
    return TRUE;
}