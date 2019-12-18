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
typedef  int INT ;
typedef  int GLenum ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int GL_CONSTANT_COLOR0_NV ; 
 int GL_CONSTANT_COLOR1_NV ; 
 int GL_PRIMARY_COLOR_NV ; 
 int GL_SECONDARY_COLOR_NV ; 
 int GL_SPARE0_NV ; 
 int GL_SPARE1_NV ; 
 int GL_TEXTURE ; 
 int GL_TEXTURE0_ARB ; 
#define  WINED3DTA_CONSTANT 134 
#define  WINED3DTA_CURRENT 133 
#define  WINED3DTA_DIFFUSE 132 
#define  WINED3DTA_SPECULAR 131 
#define  WINED3DTA_TEMP 130 
#define  WINED3DTA_TEXTURE 129 
#define  WINED3DTA_TFACTOR 128 

__attribute__((used)) static GLenum d3dta_to_combiner_input(DWORD d3dta, DWORD stage, INT texture_idx) {
    switch (d3dta) {
        case WINED3DTA_DIFFUSE:
            return GL_PRIMARY_COLOR_NV;

        case WINED3DTA_CURRENT:
            if (stage) return GL_SPARE0_NV;
            else return GL_PRIMARY_COLOR_NV;

        case WINED3DTA_TEXTURE:
            if (texture_idx > -1) return GL_TEXTURE0_ARB + texture_idx;
            else return GL_PRIMARY_COLOR_NV;

        case WINED3DTA_TFACTOR:
            return GL_CONSTANT_COLOR0_NV;

        case WINED3DTA_SPECULAR:
            return GL_SECONDARY_COLOR_NV;

        case WINED3DTA_TEMP:
            return GL_SPARE1_NV;

        case WINED3DTA_CONSTANT:
            /* TODO: Support per stage constants (WINED3D_TSS_CONSTANT, NV_register_combiners2) */
            FIXME("WINED3DTA_CONSTANT, not properly supported.\n");
            return GL_CONSTANT_COLOR1_NV;

        default:
            FIXME("Unrecognized texture arg %#x\n", d3dta);
            return GL_TEXTURE;
    }
}