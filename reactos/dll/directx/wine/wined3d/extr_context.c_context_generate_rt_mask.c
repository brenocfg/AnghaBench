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
typedef  int GLenum ;
typedef  unsigned int DWORD ;

/* Variables and functions */

__attribute__((used)) static inline DWORD context_generate_rt_mask(GLenum buffer)
{
    /* Should take care of all the GL_FRONT/GL_BACK/GL_AUXi/GL_NONE... cases */
    return buffer ? (1u << 31) | buffer : 0;
}