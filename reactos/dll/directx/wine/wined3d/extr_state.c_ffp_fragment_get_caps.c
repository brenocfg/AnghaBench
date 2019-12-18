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
struct TYPE_2__ {int /*<<< orphan*/  textures; } ;
struct wined3d_gl_info {TYPE_1__ limits; scalar_t__* supported; } ;
struct fragment_caps {int TextureOpCaps; int /*<<< orphan*/  MaxSimultaneousTextures; int /*<<< orphan*/  MaxTextureBlendStages; scalar_t__ PrimitiveMiscCaps; scalar_t__ wined3d_caps; } ;

/* Variables and functions */
 size_t ARB_TEXTURE_ENV_COMBINE ; 
 size_t ARB_TEXTURE_ENV_DOT3 ; 
 size_t ATI_TEXTURE_ENV_COMBINE3 ; 
 size_t EXT_TEXTURE_ENV_COMBINE ; 
 size_t NV_TEXTURE_ENV_COMBINE4 ; 
 int WINED3DTEXOPCAPS_ADD ; 
 int WINED3DTEXOPCAPS_ADDSIGNED ; 
 int WINED3DTEXOPCAPS_ADDSIGNED2X ; 
 int WINED3DTEXOPCAPS_ADDSMOOTH ; 
 int WINED3DTEXOPCAPS_BLENDCURRENTALPHA ; 
 int WINED3DTEXOPCAPS_BLENDDIFFUSEALPHA ; 
 int WINED3DTEXOPCAPS_BLENDFACTORALPHA ; 
 int WINED3DTEXOPCAPS_BLENDTEXTUREALPHA ; 
 int WINED3DTEXOPCAPS_BLENDTEXTUREALPHAPM ; 
 int WINED3DTEXOPCAPS_DISABLE ; 
 int WINED3DTEXOPCAPS_DOTPRODUCT3 ; 
 int WINED3DTEXOPCAPS_LERP ; 
 int WINED3DTEXOPCAPS_MODULATE ; 
 int WINED3DTEXOPCAPS_MODULATE2X ; 
 int WINED3DTEXOPCAPS_MODULATE4X ; 
 int WINED3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR ; 
 int WINED3DTEXOPCAPS_MODULATECOLOR_ADDALPHA ; 
 int WINED3DTEXOPCAPS_MULTIPLYADD ; 
 int WINED3DTEXOPCAPS_SELECTARG1 ; 
 int WINED3DTEXOPCAPS_SELECTARG2 ; 
 int WINED3DTEXOPCAPS_SUBTRACT ; 

__attribute__((used)) static void ffp_fragment_get_caps(const struct wined3d_gl_info *gl_info, struct fragment_caps *caps)
{
    caps->wined3d_caps = 0;
    caps->PrimitiveMiscCaps = 0;
    caps->TextureOpCaps = WINED3DTEXOPCAPS_ADD
            | WINED3DTEXOPCAPS_ADDSIGNED
            | WINED3DTEXOPCAPS_ADDSIGNED2X
            | WINED3DTEXOPCAPS_MODULATE
            | WINED3DTEXOPCAPS_MODULATE2X
            | WINED3DTEXOPCAPS_MODULATE4X
            | WINED3DTEXOPCAPS_SELECTARG1
            | WINED3DTEXOPCAPS_SELECTARG2
            | WINED3DTEXOPCAPS_DISABLE;

    if (gl_info->supported[ARB_TEXTURE_ENV_COMBINE]
            || gl_info->supported[EXT_TEXTURE_ENV_COMBINE]
            || gl_info->supported[NV_TEXTURE_ENV_COMBINE4])
    {
        caps->TextureOpCaps |= WINED3DTEXOPCAPS_BLENDDIFFUSEALPHA
                | WINED3DTEXOPCAPS_BLENDTEXTUREALPHA
                | WINED3DTEXOPCAPS_BLENDFACTORALPHA
                | WINED3DTEXOPCAPS_BLENDCURRENTALPHA
                | WINED3DTEXOPCAPS_LERP
                | WINED3DTEXOPCAPS_SUBTRACT;
    }
    if (gl_info->supported[ATI_TEXTURE_ENV_COMBINE3]
            || gl_info->supported[NV_TEXTURE_ENV_COMBINE4])
    {
        caps->TextureOpCaps |= WINED3DTEXOPCAPS_ADDSMOOTH
                | WINED3DTEXOPCAPS_MULTIPLYADD
                | WINED3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR
                | WINED3DTEXOPCAPS_MODULATECOLOR_ADDALPHA
                | WINED3DTEXOPCAPS_BLENDTEXTUREALPHAPM;
    }
    if (gl_info->supported[ARB_TEXTURE_ENV_DOT3])
        caps->TextureOpCaps |= WINED3DTEXOPCAPS_DOTPRODUCT3;

    caps->MaxTextureBlendStages = gl_info->limits.textures;
    caps->MaxSimultaneousTextures = gl_info->limits.textures;
}