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
struct wined3d_shader_signature_element {char* semantic_name; int semantic_idx; size_t register_idx; } ;
struct TYPE_3__ {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;
struct wined3d_shader {TYPE_1__ input_signature; } ;
struct shader_arb_ctx_priv {char** ps_input; } ;
struct TYPE_4__ {int vp_mode; } ;
struct arb_ps_compile_args {TYPE_2__ super; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,size_t,char const*,int,char*) ; 
 int /*<<< orphan*/  WINED3D_DECL_USAGE_COLOR ; 
 int /*<<< orphan*/  WINED3D_DECL_USAGE_FOG ; 
 int /*<<< orphan*/  WINED3D_DECL_USAGE_TEXCOORD ; 
#define  fixedfunction 130 
#define  pretransformed 129 
 int /*<<< orphan*/  shader_match_semantic (char const*,int /*<<< orphan*/ ) ; 
#define  vertexshader 128 

__attribute__((used)) static void init_ps_input(const struct wined3d_shader *shader,
        const struct arb_ps_compile_args *args, struct shader_arb_ctx_priv *priv)
{
    static const char * const texcoords[8] =
    {
        "fragment.texcoord[0]", "fragment.texcoord[1]", "fragment.texcoord[2]", "fragment.texcoord[3]",
        "fragment.texcoord[4]", "fragment.texcoord[5]", "fragment.texcoord[6]", "fragment.texcoord[7]"
    };
    unsigned int i;
    const struct wined3d_shader_signature_element *input;
    const char *semantic_name;
    DWORD semantic_idx;

    switch(args->super.vp_mode)
    {
        case pretransformed:
        case fixedfunction:
            /* The pixelshader has to collect the varyings on its own. In any case properly load
             * color0 and color1. In the case of pretransformed vertices also load texcoords. Set
             * other attribs to 0.0.
             *
             * For fixedfunction this behavior is correct, according to the tests. For pretransformed
             * we'd either need a replacement shader that can load other attribs like BINORMAL, or
             * load the texcoord attrib pointers to match the pixel shader signature
             */
            for (i = 0; i < shader->input_signature.element_count; ++i)
            {
                input = &shader->input_signature.elements[i];
                if (!(semantic_name = input->semantic_name))
                    continue;
                semantic_idx = input->semantic_idx;

                if (shader_match_semantic(semantic_name, WINED3D_DECL_USAGE_COLOR))
                {
                    if (!semantic_idx)
                        priv->ps_input[input->register_idx] = "fragment.color.primary";
                    else if (semantic_idx == 1)
                        priv->ps_input[input->register_idx] = "fragment.color.secondary";
                    else
                        priv->ps_input[input->register_idx] = "0.0";
                }
                else if (args->super.vp_mode == fixedfunction)
                {
                    priv->ps_input[input->register_idx] = "0.0";
                }
                else if (shader_match_semantic(semantic_name, WINED3D_DECL_USAGE_TEXCOORD))
                {
                    if (semantic_idx < 8)
                        priv->ps_input[input->register_idx] = texcoords[semantic_idx];
                    else
                        priv->ps_input[input->register_idx] = "0.0";
                }
                else if (shader_match_semantic(semantic_name, WINED3D_DECL_USAGE_FOG))
                {
                    if (!semantic_idx)
                        priv->ps_input[input->register_idx] = "fragment.fogcoord";
                    else
                        priv->ps_input[input->register_idx] = "0.0";
                }
                else
                {
                    priv->ps_input[input->register_idx] = "0.0";
                }

                TRACE("v%u, semantic %s%u is %s\n", input->register_idx,
                        semantic_name, semantic_idx, priv->ps_input[input->register_idx]);
            }
            break;

        case vertexshader:
            /* That one is easy. The vertex shaders provide v0-v7 in fragment.texcoord and v8 and v9 in
             * fragment.color
             */
            for(i = 0; i < 8; i++)
            {
                priv->ps_input[i] = texcoords[i];
            }
            priv->ps_input[8] = "fragment.color.primary";
            priv->ps_input[9] = "fragment.color.secondary";
            break;
    }
}