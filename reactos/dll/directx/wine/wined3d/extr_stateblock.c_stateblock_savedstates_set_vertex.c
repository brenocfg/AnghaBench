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
struct wined3d_saved_states {int vertexDecl; int vertexShader; unsigned int* renderState; int* textureState; unsigned int* samplerState; int vertexShaderConstantsB; int vertexShaderConstantsI; int /*<<< orphan*/  vs_consts_f; } ;
typedef  unsigned int WORD ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 unsigned int MAX_COMBINED_SAMPLERS ; 
 unsigned int MAX_TEXTURES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int* vertex_states_render ; 
 unsigned int* vertex_states_sampler ; 
 unsigned int* vertex_states_texture ; 

__attribute__((used)) static void stateblock_savedstates_set_vertex(struct wined3d_saved_states *states, const DWORD num_constants)
{
    DWORD texture_mask = 0;
    WORD sampler_mask = 0;
    unsigned int i;

    states->vertexDecl = 1;
    states->vertexShader = 1;

    for (i = 0; i < ARRAY_SIZE(vertex_states_render); ++i)
    {
        DWORD rs = vertex_states_render[i];
        states->renderState[rs >> 5] |= 1u << (rs & 0x1f);
    }

    for (i = 0; i < ARRAY_SIZE(vertex_states_texture); ++i)
        texture_mask |= 1u << vertex_states_texture[i];
    for (i = 0; i < MAX_TEXTURES; ++i) states->textureState[i] = texture_mask;
    for (i = 0; i < ARRAY_SIZE(vertex_states_sampler); ++i)
        sampler_mask |= 1u << vertex_states_sampler[i];
    for (i = 0; i < MAX_COMBINED_SAMPLERS; ++i) states->samplerState[i] = sampler_mask;
    states->vertexShaderConstantsB = 0xffff;
    states->vertexShaderConstantsI = 0xffff;

    memset(states->vs_consts_f, TRUE, sizeof(BOOL) * num_constants);
}