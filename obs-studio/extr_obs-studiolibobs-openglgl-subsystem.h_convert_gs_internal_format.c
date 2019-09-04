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
 int /*<<< orphan*/  GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ; 
 int /*<<< orphan*/  GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ; 
 int /*<<< orphan*/  GL_COMPRESSED_RGBA_S3TC_DXT5_EXT ; 
 int /*<<< orphan*/  GL_R16 ; 
 int /*<<< orphan*/  GL_R16F ; 
 int /*<<< orphan*/  GL_R32F ; 
 int /*<<< orphan*/  GL_R8 ; 
 int /*<<< orphan*/  GL_RG16F ; 
 int /*<<< orphan*/  GL_RG32F ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_RGB10_A2 ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_RGBA16 ; 
 int /*<<< orphan*/  GL_RGBA16F ; 
 int /*<<< orphan*/  GL_RGBA32F ; 
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

__attribute__((used)) static inline GLenum convert_gs_internal_format(enum gs_color_format format)
{
	switch (format) {
	case GS_A8:          return GL_R8; /* NOTE: use GL_TEXTURE_SWIZZLE_x */
	case GS_R8:          return GL_R8;
	case GS_RGBA:        return GL_RGBA;
	case GS_BGRX:        return GL_RGB;
	case GS_BGRA:        return GL_RGBA;
	case GS_R10G10B10A2: return GL_RGB10_A2;
	case GS_RGBA16:      return GL_RGBA16;
	case GS_R16:         return GL_R16;
	case GS_RGBA16F:     return GL_RGBA16F;
	case GS_RGBA32F:     return GL_RGBA32F;
	case GS_RG16F:       return GL_RG16F;
	case GS_RG32F:       return GL_RG32F;
	case GS_R8G8:        return GL_R16;
	case GS_R16F:        return GL_R16F;
	case GS_R32F:        return GL_R32F;
	case GS_DXT1:        return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	case GS_DXT3:        return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case GS_DXT5:        return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	case GS_UNKNOWN:     return 0;
	}

	return 0;
}