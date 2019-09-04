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
typedef  enum gs_zstencil_format { ____Placeholder_gs_zstencil_format } gs_zstencil_format ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DEPTH24_STENCIL8 ; 
 int /*<<< orphan*/  GL_DEPTH32F_STENCIL8 ; 
 int /*<<< orphan*/  GL_DEPTH_COMPONENT16 ; 
 int /*<<< orphan*/  GL_DEPTH_COMPONENT32F ; 
#define  GS_Z16 132 
#define  GS_Z24_S8 131 
#define  GS_Z32F 130 
#define  GS_Z32F_S8X24 129 
#define  GS_ZS_NONE 128 

__attribute__((used)) static inline GLenum convert_zstencil_format(enum gs_zstencil_format format)
{
	switch (format) {
	case GS_Z16:         return GL_DEPTH_COMPONENT16;
	case GS_Z24_S8:      return GL_DEPTH24_STENCIL8;
	case GS_Z32F:        return GL_DEPTH_COMPONENT32F;
	case GS_Z32F_S8X24:  return GL_DEPTH32F_STENCIL8;
	case GS_ZS_NONE:     return 0;
	}

	return 0;
}