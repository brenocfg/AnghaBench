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
struct TYPE_2__ {int /*<<< orphan*/  textures; int /*<<< orphan*/  general_combiners; } ;
struct wined3d_gl_info {TYPE_1__ limits; scalar_t__* supported; } ;
struct fragment_caps {int TextureOpCaps; int /*<<< orphan*/  MaxSimultaneousTextures; int /*<<< orphan*/  MaxTextureBlendStages; int /*<<< orphan*/  PrimitiveMiscCaps; scalar_t__ wined3d_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TEXTURES ; 
 size_t NV_REGISTER_COMBINERS2 ; 
 size_t NV_TEXTURE_SHADER2 ; 
 int /*<<< orphan*/  WINED3DPMISCCAPS_PERSTAGECONSTANT ; 
 int /*<<< orphan*/  WINED3DPMISCCAPS_TSSARGTEMP ; 
 int WINED3DTEXOPCAPS_ADD ; 
 int WINED3DTEXOPCAPS_ADDSIGNED ; 
 int WINED3DTEXOPCAPS_ADDSIGNED2X ; 
 int WINED3DTEXOPCAPS_ADDSMOOTH ; 
 int WINED3DTEXOPCAPS_BLENDCURRENTALPHA ; 
 int WINED3DTEXOPCAPS_BLENDDIFFUSEALPHA ; 
 int WINED3DTEXOPCAPS_BLENDFACTORALPHA ; 
 int WINED3DTEXOPCAPS_BLENDTEXTUREALPHA ; 
 int WINED3DTEXOPCAPS_BLENDTEXTUREALPHAPM ; 
 int WINED3DTEXOPCAPS_BUMPENVMAP ; 
 int WINED3DTEXOPCAPS_DISABLE ; 
 int WINED3DTEXOPCAPS_DOTPRODUCT3 ; 
 int WINED3DTEXOPCAPS_LERP ; 
 int WINED3DTEXOPCAPS_MODULATE ; 
 int WINED3DTEXOPCAPS_MODULATE2X ; 
 int WINED3DTEXOPCAPS_MODULATE4X ; 
 int WINED3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR ; 
 int WINED3DTEXOPCAPS_MODULATECOLOR_ADDALPHA ; 
 int WINED3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR ; 
 int WINED3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA ; 
 int WINED3DTEXOPCAPS_MULTIPLYADD ; 
 int WINED3DTEXOPCAPS_SELECTARG1 ; 
 int WINED3DTEXOPCAPS_SELECTARG2 ; 
 int WINED3DTEXOPCAPS_SUBTRACT ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvrc_fragment_get_caps(const struct wined3d_gl_info *gl_info, struct fragment_caps *caps)
{
    caps->wined3d_caps = 0;
    caps->PrimitiveMiscCaps = WINED3DPMISCCAPS_TSSARGTEMP;

    /* The caps below can be supported but aren't handled yet in utils.c
     * 'd3dta_to_combiner_input', disable them until support is fixed */
#if 0
    if (gl_info->supported[NV_REGISTER_COMBINERS2])
        caps->PrimitiveMiscCaps |=  WINED3DPMISCCAPS_PERSTAGECONSTANT;
#endif

    caps->TextureOpCaps = WINED3DTEXOPCAPS_ADD
            | WINED3DTEXOPCAPS_ADDSIGNED
            | WINED3DTEXOPCAPS_ADDSIGNED2X
            | WINED3DTEXOPCAPS_MODULATE
            | WINED3DTEXOPCAPS_MODULATE2X
            | WINED3DTEXOPCAPS_MODULATE4X
            | WINED3DTEXOPCAPS_SELECTARG1
            | WINED3DTEXOPCAPS_SELECTARG2
            | WINED3DTEXOPCAPS_DISABLE
            | WINED3DTEXOPCAPS_BLENDDIFFUSEALPHA
            | WINED3DTEXOPCAPS_BLENDTEXTUREALPHA
            | WINED3DTEXOPCAPS_BLENDFACTORALPHA
            | WINED3DTEXOPCAPS_BLENDCURRENTALPHA
            | WINED3DTEXOPCAPS_LERP
            | WINED3DTEXOPCAPS_SUBTRACT
            | WINED3DTEXOPCAPS_ADDSMOOTH
            | WINED3DTEXOPCAPS_MULTIPLYADD
            | WINED3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR
            | WINED3DTEXOPCAPS_MODULATECOLOR_ADDALPHA
            | WINED3DTEXOPCAPS_BLENDTEXTUREALPHAPM
            | WINED3DTEXOPCAPS_DOTPRODUCT3
            | WINED3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR
            | WINED3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA;

    if (gl_info->supported[NV_TEXTURE_SHADER2])
    {
        /* Bump mapping is supported already in NV_TEXTURE_SHADER, but that extension does
         * not support 3D textures. This asks for trouble if an app uses both bump mapping
         * and 3D textures. It also allows us to keep the code simpler by having texture
         * shaders constantly enabled. */
        caps->TextureOpCaps |= WINED3DTEXOPCAPS_BUMPENVMAP;
        /* TODO: Luminance bump map? */
    }

#if 0
    /* FIXME: Add
            caps->TextureOpCaps |= WINED3DTEXOPCAPS_BUMPENVMAPLUMINANCE
            WINED3DTEXOPCAPS_PREMODULATE */
#endif

    caps->MaxTextureBlendStages = min(MAX_TEXTURES, gl_info->limits.general_combiners);
    caps->MaxSimultaneousTextures = gl_info->limits.textures;
}