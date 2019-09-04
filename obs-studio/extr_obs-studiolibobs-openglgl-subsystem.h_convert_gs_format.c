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
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BGRA ; 
 int /*<<< orphan*/  GL_RED ; 
 int /*<<< orphan*/  GL_RG ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_RGBA ; 
#define  GS_A8 146 
#define  GS_BGRA 145 
#define  GS_BGRX 144 
#define  GS_DXT1 143 
#define  GS_DXT3 142 
#define  GS_DXT5 141 
#define  GS_R10G10B10A2 140 
#define  GS_R16 139 
#define  GS_R16F 138 
#define  GS_R32F 137 
#define  GS_R8 136 
#define  GS_R8G8 135 
#define  GS_RG16F 134 
#define  GS_RG32F 133 
#define  GS_RGBA 132 
#define  GS_RGBA16 131 
#define  GS_RGBA16F 130 
#define  GS_RGBA32F 129 
#define  GS_UNKNOWN 128 

__attribute__((used)) static inline GLenum convert_gs_format(enum gs_color_format format)
{
	switch (format) {
	case GS_A8:          return GL_RED;
	case GS_R8:          return GL_RED;
	case GS_RGBA:        return GL_RGBA;
	case GS_BGRX:        return GL_BGRA;
	case GS_BGRA:        return GL_BGRA;
	case GS_R10G10B10A2: return GL_RGBA;
	case GS_RGBA16:      return GL_RGBA;
	case GS_R16:         return GL_RED;
	case GS_RGBA16F:     return GL_RGBA;
	case GS_RGBA32F:     return GL_RGBA;
	case GS_RG16F:       return GL_RG;
	case GS_RG32F:       return GL_RG;
	case GS_R8G8:        return GL_RG;
	case GS_R16F:        return GL_RED;
	case GS_R32F:        return GL_RED;
	case GS_DXT1:        return GL_RGB;
	case GS_DXT3:        return GL_RGBA;
	case GS_DXT5:        return GL_RGBA;
	case GS_UNKNOWN:     return 0;
	}

	return 0;
}