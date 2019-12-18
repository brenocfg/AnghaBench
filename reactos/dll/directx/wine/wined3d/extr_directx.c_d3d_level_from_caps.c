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
struct shader_caps {int vs_version; } ;
struct fragment_caps {int TextureOpCaps; int MaxSimultaneousTextures; } ;
typedef  enum wined3d_d3d_level { ____Placeholder_wined3d_d3d_level } wined3d_d3d_level ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ MAKEDWORD_VERSION (int,int) ; 
 int WINED3DTEXOPCAPS_DOTPRODUCT3 ; 
 int WINED3D_D3D_LEVEL_10 ; 
 int WINED3D_D3D_LEVEL_11 ; 
 int WINED3D_D3D_LEVEL_5 ; 
 int WINED3D_D3D_LEVEL_6 ; 
 int WINED3D_D3D_LEVEL_7 ; 
 int WINED3D_D3D_LEVEL_8 ; 
 int WINED3D_D3D_LEVEL_9_SM2 ; 
 int WINED3D_D3D_LEVEL_9_SM3 ; 

__attribute__((used)) static enum wined3d_d3d_level d3d_level_from_caps(const struct shader_caps *shader_caps, const struct fragment_caps *fragment_caps, DWORD glsl_version)
{
    if (shader_caps->vs_version >= 5)
        return WINED3D_D3D_LEVEL_11;
    if (shader_caps->vs_version == 4)
        return WINED3D_D3D_LEVEL_10;
    if (shader_caps->vs_version == 3)
    {
        /* wined3d with default settings at the moment doesn't expose SM4+ on
         * Mesa drivers. */
        if (glsl_version >= MAKEDWORD_VERSION(4, 30))
            return WINED3D_D3D_LEVEL_11;
        if (glsl_version >= MAKEDWORD_VERSION(1, 30))
            return WINED3D_D3D_LEVEL_10;
        return WINED3D_D3D_LEVEL_9_SM3;
    }
    if (shader_caps->vs_version == 2)
        return WINED3D_D3D_LEVEL_9_SM2;
    if (shader_caps->vs_version == 1)
        return WINED3D_D3D_LEVEL_8;

    if (fragment_caps->TextureOpCaps & WINED3DTEXOPCAPS_DOTPRODUCT3)
        return WINED3D_D3D_LEVEL_7;
    if (fragment_caps->MaxSimultaneousTextures > 1)
        return WINED3D_D3D_LEVEL_6;

    return WINED3D_D3D_LEVEL_5;
}