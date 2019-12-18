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
#define  GL_CON_0_ATI 145 
#define  GL_CON_1_ATI 144 
#define  GL_CON_2_ATI 143 
#define  GL_CON_3_ATI 142 
#define  GL_CON_4_ATI 141 
#define  GL_CON_5_ATI 140 
#define  GL_CON_6_ATI 139 
#define  GL_CON_7_ATI 138 
#define  GL_ONE 137 
#define  GL_PRIMARY_COLOR 136 
#define  GL_REG_0_ATI 135 
#define  GL_REG_1_ATI 134 
#define  GL_REG_2_ATI 133 
#define  GL_REG_3_ATI 132 
#define  GL_REG_4_ATI 131 
#define  GL_REG_5_ATI 130 
#define  GL_SECONDARY_INTERPOLATOR_ATI 129 
#define  GL_ZERO 128 

__attribute__((used)) static const char *debug_register(GLuint reg) {
    switch(reg) {
        case GL_REG_0_ATI:                  return "GL_REG_0_ATI";
        case GL_REG_1_ATI:                  return "GL_REG_1_ATI";
        case GL_REG_2_ATI:                  return "GL_REG_2_ATI";
        case GL_REG_3_ATI:                  return "GL_REG_3_ATI";
        case GL_REG_4_ATI:                  return "GL_REG_4_ATI";
        case GL_REG_5_ATI:                  return "GL_REG_5_ATI";

        case GL_CON_0_ATI:                  return "GL_CON_0_ATI";
        case GL_CON_1_ATI:                  return "GL_CON_1_ATI";
        case GL_CON_2_ATI:                  return "GL_CON_2_ATI";
        case GL_CON_3_ATI:                  return "GL_CON_3_ATI";
        case GL_CON_4_ATI:                  return "GL_CON_4_ATI";
        case GL_CON_5_ATI:                  return "GL_CON_5_ATI";
        case GL_CON_6_ATI:                  return "GL_CON_6_ATI";
        case GL_CON_7_ATI:                  return "GL_CON_7_ATI";

        case GL_ZERO:                       return "GL_ZERO";
        case GL_ONE:                        return "GL_ONE";
        case GL_PRIMARY_COLOR:              return "GL_PRIMARY_COLOR";
        case GL_SECONDARY_INTERPOLATOR_ATI: return "GL_SECONDARY_INTERPOLATOR_ATI";

        default:                            return "Unknown register\n";
    }
}