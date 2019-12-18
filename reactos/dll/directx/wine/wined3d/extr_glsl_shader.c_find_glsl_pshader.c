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
struct wined3d_string_buffer_list {int dummy; } ;
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader {struct glsl_shader_private* backend_data; } ;
struct wined3d_context {int dummy; } ;
struct ps_np2fixup_info {int dummy; } ;
struct ps_compile_args {int /*<<< orphan*/  tex_types; scalar_t__ np2_fixup; } ;
struct TYPE_2__ {struct glsl_ps_compiled_shader* ps; } ;
struct glsl_shader_private {size_t num_gl_shaders; size_t shader_array_size; TYPE_1__ gl_shaders; } ;
struct glsl_ps_compiled_shader {int /*<<< orphan*/  id; struct ps_np2fixup_info np2fixup; struct ps_compile_args args; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_shader*) ; 
 struct glsl_ps_compiled_shader* heap_alloc (int) ; 
 struct glsl_shader_private* heap_alloc_zero (int) ; 
 struct glsl_ps_compiled_shader* heap_realloc (struct glsl_ps_compiled_shader*,int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcmp (struct ps_compile_args*,struct ps_compile_args const*,int) ; 
 int /*<<< orphan*/  memset (struct ps_np2fixup_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pixelshader_update_resource_types (struct wined3d_shader*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_pshader (struct wined3d_context const*,struct wined3d_string_buffer*,struct wined3d_string_buffer_list*,struct wined3d_shader*,struct ps_compile_args const*,struct ps_np2fixup_info*) ; 
 int /*<<< orphan*/  string_buffer_clear (struct wined3d_string_buffer*) ; 

__attribute__((used)) static GLuint find_glsl_pshader(const struct wined3d_context *context,
        struct wined3d_string_buffer *buffer, struct wined3d_string_buffer_list *string_buffers,
        struct wined3d_shader *shader,
        const struct ps_compile_args *args, const struct ps_np2fixup_info **np2fixup_info)
{
    struct glsl_ps_compiled_shader *gl_shaders, *new_array;
    struct glsl_shader_private *shader_data;
    struct ps_np2fixup_info *np2fixup;
    UINT i;
    DWORD new_size;
    GLuint ret;

    if (!shader->backend_data)
    {
        if (!(shader->backend_data = heap_alloc_zero(sizeof(*shader_data))))
        {
            ERR("Failed to allocate backend data.\n");
            return 0;
        }
    }
    shader_data = shader->backend_data;
    gl_shaders = shader_data->gl_shaders.ps;

    /* Usually we have very few GL shaders for each d3d shader(just 1 or maybe 2),
     * so a linear search is more performant than a hashmap or a binary search
     * (cache coherency etc)
     */
    for (i = 0; i < shader_data->num_gl_shaders; ++i)
    {
        if (!memcmp(&gl_shaders[i].args, args, sizeof(*args)))
        {
            if (args->np2_fixup)
                *np2fixup_info = &gl_shaders[i].np2fixup;
            return gl_shaders[i].id;
        }
    }

    TRACE("No matching GL shader found for shader %p, compiling a new shader.\n", shader);
    if (shader_data->shader_array_size == shader_data->num_gl_shaders)
    {
        if (shader_data->num_gl_shaders)
        {
            new_size = shader_data->shader_array_size + max(1, shader_data->shader_array_size / 2);
            new_array = heap_realloc(shader_data->gl_shaders.ps, new_size * sizeof(*gl_shaders));
        }
        else
        {
            new_array = heap_alloc(sizeof(*gl_shaders));
            new_size = 1;
        }

        if(!new_array) {
            ERR("Out of memory\n");
            return 0;
        }
        shader_data->gl_shaders.ps = new_array;
        shader_data->shader_array_size = new_size;
        gl_shaders = new_array;
    }

    gl_shaders[shader_data->num_gl_shaders].args = *args;

    np2fixup = &gl_shaders[shader_data->num_gl_shaders].np2fixup;
    memset(np2fixup, 0, sizeof(*np2fixup));
    *np2fixup_info = args->np2_fixup ? np2fixup : NULL;

    pixelshader_update_resource_types(shader, args->tex_types);

    string_buffer_clear(buffer);
    ret = shader_glsl_generate_pshader(context, buffer, string_buffers, shader, args, np2fixup);
    gl_shaders[shader_data->num_gl_shaders++].id = ret;

    return ret;
}