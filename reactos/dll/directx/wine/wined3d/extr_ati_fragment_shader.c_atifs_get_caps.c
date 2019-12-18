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
struct wined3d_gl_info {int dummy; } ;
struct fragment_caps {int PrimitiveMiscCaps; int TextureOpCaps; int MaxSimultaneousTextures; int /*<<< orphan*/  MaxTextureBlendStages; int /*<<< orphan*/  wined3d_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TEXTURES ; 
 int WINED3DPMISCCAPS_PERSTAGECONSTANT ; 
 int WINED3DPMISCCAPS_TSSARGTEMP ; 
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
 int /*<<< orphan*/  WINED3D_FRAGMENT_CAP_PROJ_CONTROL ; 

__attribute__((used)) static void atifs_get_caps(const struct wined3d_gl_info *gl_info, struct fragment_caps *caps)
{
    caps->wined3d_caps = WINED3D_FRAGMENT_CAP_PROJ_CONTROL;
    caps->PrimitiveMiscCaps = WINED3DPMISCCAPS_TSSARGTEMP               |
            WINED3DPMISCCAPS_PERSTAGECONSTANT;
    caps->TextureOpCaps =  WINED3DTEXOPCAPS_DISABLE                     |
                           WINED3DTEXOPCAPS_SELECTARG1                  |
                           WINED3DTEXOPCAPS_SELECTARG2                  |
                           WINED3DTEXOPCAPS_MODULATE4X                  |
                           WINED3DTEXOPCAPS_MODULATE2X                  |
                           WINED3DTEXOPCAPS_MODULATE                    |
                           WINED3DTEXOPCAPS_ADDSIGNED2X                 |
                           WINED3DTEXOPCAPS_ADDSIGNED                   |
                           WINED3DTEXOPCAPS_ADD                         |
                           WINED3DTEXOPCAPS_SUBTRACT                    |
                           WINED3DTEXOPCAPS_ADDSMOOTH                   |
                           WINED3DTEXOPCAPS_BLENDCURRENTALPHA           |
                           WINED3DTEXOPCAPS_BLENDFACTORALPHA            |
                           WINED3DTEXOPCAPS_BLENDTEXTUREALPHA           |
                           WINED3DTEXOPCAPS_BLENDDIFFUSEALPHA           |
                           WINED3DTEXOPCAPS_BLENDTEXTUREALPHAPM         |
                           WINED3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR      |
                           WINED3DTEXOPCAPS_MODULATECOLOR_ADDALPHA      |
                           WINED3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA   |
                           WINED3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR   |
                           WINED3DTEXOPCAPS_DOTPRODUCT3                 |
                           WINED3DTEXOPCAPS_MULTIPLYADD                 |
                           WINED3DTEXOPCAPS_LERP                        |
                           WINED3DTEXOPCAPS_BUMPENVMAP;

    /* TODO: Implement WINED3DTEXOPCAPS_BUMPENVMAPLUMINANCE
    and WINED3DTEXOPCAPS_PREMODULATE */

    /* GL_ATI_fragment_shader always supports 6 textures, which was the limit on r200 cards
     * which this extension is exclusively focused on(later cards have GL_ARB_fragment_program).
     * If the current card has more than 8 fixed function textures in OpenGL's regular fixed
     * function pipeline then the ATI_fragment_shader backend imposes a stricter limit. This
     * shouldn't be too hard since Nvidia cards have a limit of 4 textures with the default ffp
     * pipeline, and almost all games are happy with that. We can however support up to 8
     * texture stages because we have a 2nd pass limit of 8 instructions, and per stage we use
     * only 1 instruction.
     *
     * The proper fix for this is not to use GL_ATI_fragment_shader on cards newer than the
     * r200 series and use an ARB or GLSL shader instead
     */
    caps->MaxTextureBlendStages   = MAX_TEXTURES;
    caps->MaxSimultaneousTextures = 6;
}