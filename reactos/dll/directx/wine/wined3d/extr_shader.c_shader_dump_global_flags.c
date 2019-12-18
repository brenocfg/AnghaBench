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
struct wined3d_string_buffer {int dummy; } ;
typedef  int DWORD ;

/* Variables and functions */
 int WINED3DSGF_ENABLE_RAW_AND_STRUCTURED_BUFFERS ; 
 int WINED3DSGF_FORCE_EARLY_DEPTH_STENCIL ; 
 int WINED3DSGF_REFACTORING_ALLOWED ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_dump_global_flags(struct wined3d_string_buffer *buffer, DWORD global_flags)
{
    if (global_flags & WINED3DSGF_REFACTORING_ALLOWED)
    {
        shader_addline(buffer, "refactoringAllowed");
        global_flags &= ~WINED3DSGF_REFACTORING_ALLOWED;
        if (global_flags)
            shader_addline(buffer, " | ");
    }

    if (global_flags & WINED3DSGF_FORCE_EARLY_DEPTH_STENCIL)
    {
        shader_addline(buffer, "forceEarlyDepthStencil");
        global_flags &= ~WINED3DSGF_FORCE_EARLY_DEPTH_STENCIL;
        if (global_flags)
            shader_addline(buffer, " | ");
    }

    if (global_flags & WINED3DSGF_ENABLE_RAW_AND_STRUCTURED_BUFFERS)
    {
        shader_addline(buffer, "enableRawAndStructuredBuffers");
        global_flags &= ~WINED3DSGF_ENABLE_RAW_AND_STRUCTURED_BUFFERS;
    }

    if (global_flags)
        shader_addline(buffer, "unknown_flags(%#x)", global_flags);
}