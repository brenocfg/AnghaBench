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
struct wined3d_saved_states {int pixelShader; unsigned int* renderState; int* textureState; unsigned int* samplerState; int pixelShaderConstantsB; int pixelShaderConstantsI; int /*<<< orphan*/  ps_consts_f; } ;
typedef  unsigned int WORD ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 unsigned int MAX_COMBINED_SAMPLERS ; 
 unsigned int MAX_TEXTURES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int* pixel_states_render ; 
 unsigned int* pixel_states_sampler ; 
 unsigned int* pixel_states_texture ; 

__attribute__((used)) static void stateblock_savedstates_set_pixel(struct wined3d_saved_states *states, const DWORD num_constants)
{
    DWORD texture_mask = 0;
    WORD sampler_mask = 0;
    unsigned int i;

    states->pixelShader = 1;

    for (i = 0; i < ARRAY_SIZE(pixel_states_render); ++i)
    {
        DWORD rs = pixel_states_render[i];
        states->renderState[rs >> 5] |= 1u << (rs & 0x1f);
    }

    for (i = 0; i < ARRAY_SIZE(pixel_states_texture); ++i)
        texture_mask |= 1u << pixel_states_texture[i];
    for (i = 0; i < MAX_TEXTURES; ++i) states->textureState[i] = texture_mask;
    for (i = 0; i < ARRAY_SIZE(pixel_states_sampler); ++i)
        sampler_mask |= 1u << pixel_states_sampler[i];
    for (i = 0; i < MAX_COMBINED_SAMPLERS; ++i) states->samplerState[i] = sampler_mask;
    states->pixelShaderConstantsB = 0xffff;
    states->pixelShaderConstantsI = 0xffff;

    memset(states->ps_consts_f, TRUE, sizeof(BOOL) * num_constants);
}