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
typedef  int DWORD ;

/* Variables and functions */
 int STATE_ACTIVELIGHT (int /*<<< orphan*/ ) ; 
 int STATE_CLIPPLANE (int /*<<< orphan*/ ) ; 
 int STATE_CONSTANT_BUFFER (int /*<<< orphan*/ ) ; 
 scalar_t__ STATE_IS_ACTIVELIGHT (int) ; 
 scalar_t__ STATE_IS_BASEVERTEXINDEX (int) ; 
 scalar_t__ STATE_IS_BLEND (int) ; 
 scalar_t__ STATE_IS_CLIPPLANE (int) ; 
 scalar_t__ STATE_IS_COLOR_KEY (int) ; 
 scalar_t__ STATE_IS_COMPUTE_CONSTANT_BUFFER (int) ; 
 scalar_t__ STATE_IS_COMPUTE_SHADER (int) ; 
 scalar_t__ STATE_IS_COMPUTE_SHADER_RESOURCE_BINDING (int) ; 
 scalar_t__ STATE_IS_COMPUTE_UNORDERED_ACCESS_VIEW_BINDING (int) ; 
 scalar_t__ STATE_IS_FRAMEBUFFER (int) ; 
 scalar_t__ STATE_IS_FRONTFACE (int) ; 
 scalar_t__ STATE_IS_GRAPHICS_CONSTANT_BUFFER (int) ; 
 scalar_t__ STATE_IS_GRAPHICS_SHADER (int) ; 
 scalar_t__ STATE_IS_GRAPHICS_SHADER_RESOURCE_BINDING (int) ; 
 scalar_t__ STATE_IS_GRAPHICS_UNORDERED_ACCESS_VIEW_BINDING (int) ; 
 scalar_t__ STATE_IS_INDEXBUFFER (int) ; 
 scalar_t__ STATE_IS_LIGHT_TYPE (int) ; 
 scalar_t__ STATE_IS_MATERIAL (int) ; 
 scalar_t__ STATE_IS_POINTSPRITECOORDORIGIN (int) ; 
 scalar_t__ STATE_IS_POINT_ENABLE (int) ; 
 scalar_t__ STATE_IS_RENDER (int) ; 
 scalar_t__ STATE_IS_SAMPLER (int) ; 
 scalar_t__ STATE_IS_SCISSORRECT (int) ; 
 scalar_t__ STATE_IS_STREAMSRC (int) ; 
 scalar_t__ STATE_IS_STREAM_OUTPUT (int) ; 
 scalar_t__ STATE_IS_TEXTURESTAGE (int) ; 
 scalar_t__ STATE_IS_TRANSFORM (int) ; 
 scalar_t__ STATE_IS_VDECL (int) ; 
 scalar_t__ STATE_IS_VIEWPORT (int) ; 
 int STATE_RENDER (int /*<<< orphan*/ ) ; 
 int STATE_SAMPLER (int /*<<< orphan*/ ) ; 
 int STATE_SHADER (int /*<<< orphan*/ ) ; 
 int STATE_TEXTURESTAGE (int,int /*<<< orphan*/ ) ; 
 int STATE_TRANSFORM (int /*<<< orphan*/ ) ; 
 int WINED3D_HIGHEST_TEXTURE_STATE ; 
 int WINED3D_SHADER_TYPE_COMPUTE ; 
 int debug_d3drenderstate (int) ; 
 int /*<<< orphan*/  debug_d3dtexturestate (int) ; 
 int debug_d3dtstype (int) ; 
 int debug_shader_type (int) ; 
 char const* wine_dbg_sprintf (char*,int,...) ; 

const char *debug_d3dstate(DWORD state)
{
    if (STATE_IS_RENDER(state))
        return wine_dbg_sprintf("STATE_RENDER(%s)", debug_d3drenderstate(state - STATE_RENDER(0)));
    if (STATE_IS_TEXTURESTAGE(state))
    {
        DWORD texture_stage = (state - STATE_TEXTURESTAGE(0, 0)) / (WINED3D_HIGHEST_TEXTURE_STATE + 1);
        DWORD texture_state = state - STATE_TEXTURESTAGE(texture_stage, 0);
        return wine_dbg_sprintf("STATE_TEXTURESTAGE(%#x, %s)",
                texture_stage, debug_d3dtexturestate(texture_state));
    }
    if (STATE_IS_SAMPLER(state))
        return wine_dbg_sprintf("STATE_SAMPLER(%#x)", state - STATE_SAMPLER(0));
    if (STATE_IS_COMPUTE_SHADER(state))
        return wine_dbg_sprintf("STATE_SHADER(%s)", debug_shader_type(WINED3D_SHADER_TYPE_COMPUTE));
    if (STATE_IS_GRAPHICS_SHADER(state))
        return wine_dbg_sprintf("STATE_SHADER(%s)", debug_shader_type(state - STATE_SHADER(0)));
    if (STATE_IS_COMPUTE_CONSTANT_BUFFER(state))
        return wine_dbg_sprintf("STATE_CONSTANT_BUFFER(%s)", debug_shader_type(WINED3D_SHADER_TYPE_COMPUTE));
    if (STATE_IS_GRAPHICS_CONSTANT_BUFFER(state))
        return wine_dbg_sprintf("STATE_CONSTANT_BUFFER(%s)", debug_shader_type(state - STATE_CONSTANT_BUFFER(0)));
    if (STATE_IS_COMPUTE_SHADER_RESOURCE_BINDING(state))
        return "STATE_COMPUTE_SHADER_RESOURCE_BINDING";
    if (STATE_IS_GRAPHICS_SHADER_RESOURCE_BINDING(state))
        return "STATE_GRAPHICS_SHADER_RESOURCE_BINDING";
    if (STATE_IS_COMPUTE_UNORDERED_ACCESS_VIEW_BINDING(state))
        return "STATE_COMPUTE_UNORDERED_ACCESS_VIEW_BINDING";
    if (STATE_IS_GRAPHICS_UNORDERED_ACCESS_VIEW_BINDING(state))
        return "STATE_GRAPHICS_UNORDERED_ACCESS_VIEW_BINDING";
    if (STATE_IS_TRANSFORM(state))
        return wine_dbg_sprintf("STATE_TRANSFORM(%s)", debug_d3dtstype(state - STATE_TRANSFORM(0)));
    if (STATE_IS_STREAMSRC(state))
        return "STATE_STREAMSRC";
    if (STATE_IS_INDEXBUFFER(state))
        return "STATE_INDEXBUFFER";
    if (STATE_IS_VDECL(state))
        return "STATE_VDECL";
    if (STATE_IS_VIEWPORT(state))
        return "STATE_VIEWPORT";
    if (STATE_IS_LIGHT_TYPE(state))
        return "STATE_LIGHT_TYPE";
    if (STATE_IS_ACTIVELIGHT(state))
        return wine_dbg_sprintf("STATE_ACTIVELIGHT(%#x)", state - STATE_ACTIVELIGHT(0));
    if (STATE_IS_SCISSORRECT(state))
        return "STATE_SCISSORRECT";
    if (STATE_IS_CLIPPLANE(state))
        return wine_dbg_sprintf("STATE_CLIPPLANE(%#x)", state - STATE_CLIPPLANE(0));
    if (STATE_IS_MATERIAL(state))
        return "STATE_MATERIAL";
    if (STATE_IS_FRONTFACE(state))
        return "STATE_FRONTFACE";
    if (STATE_IS_POINTSPRITECOORDORIGIN(state))
        return "STATE_POINTSPRITECOORDORIGIN";
    if (STATE_IS_BASEVERTEXINDEX(state))
        return "STATE_BASEVERTEXINDEX";
    if (STATE_IS_FRAMEBUFFER(state))
        return "STATE_FRAMEBUFFER";
    if (STATE_IS_POINT_ENABLE(state))
        return "STATE_POINT_ENABLE";
    if (STATE_IS_COLOR_KEY(state))
        return "STATE_COLOR_KEY";
    if (STATE_IS_STREAM_OUTPUT(state))
        return "STATE_STREAM_OUTPUT";
    if (STATE_IS_BLEND(state))
        return "STATE_BLEND";

    return wine_dbg_sprintf("UNKNOWN_STATE(%#x)", state);
}