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
typedef  int GLuint ;

/* Variables and functions */
#define  GL_SWIZZLE_STQ_ATI 131 
#define  GL_SWIZZLE_STQ_DQ_ATI 130 
#define  GL_SWIZZLE_STR_ATI 129 
#define  GL_SWIZZLE_STR_DR_ATI 128 

__attribute__((used)) static const char *debug_swizzle(GLuint swizzle) {
    switch(swizzle) {
        case GL_SWIZZLE_STR_ATI:        return "GL_SWIZZLE_STR_ATI";
        case GL_SWIZZLE_STQ_ATI:        return "GL_SWIZZLE_STQ_ATI";
        case GL_SWIZZLE_STR_DR_ATI:     return "GL_SWIZZLE_STR_DR_ATI";
        case GL_SWIZZLE_STQ_DQ_ATI:     return "GL_SWIZZLE_STQ_DQ_ATI";
        default:                        return "unknown swizzle";
    }
}