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
typedef  enum gs_blend_type { ____Placeholder_gs_blend_type } gs_blend_type ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DST_ALPHA ; 
 int /*<<< orphan*/  GL_DST_COLOR ; 
 int /*<<< orphan*/  GL_ONE ; 
 int /*<<< orphan*/  GL_ONE_MINUS_DST_ALPHA ; 
 int /*<<< orphan*/  GL_ONE_MINUS_DST_COLOR ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_COLOR ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_SRC_ALPHA_SATURATE ; 
 int /*<<< orphan*/  GL_SRC_COLOR ; 
 int /*<<< orphan*/  GL_ZERO ; 
#define  GS_BLEND_DSTALPHA 138 
#define  GS_BLEND_DSTCOLOR 137 
#define  GS_BLEND_INVDSTALPHA 136 
#define  GS_BLEND_INVDSTCOLOR 135 
#define  GS_BLEND_INVSRCALPHA 134 
#define  GS_BLEND_INVSRCCOLOR 133 
#define  GS_BLEND_ONE 132 
#define  GS_BLEND_SRCALPHA 131 
#define  GS_BLEND_SRCALPHASAT 130 
#define  GS_BLEND_SRCCOLOR 129 
#define  GS_BLEND_ZERO 128 

__attribute__((used)) static inline GLenum convert_gs_blend_type(enum gs_blend_type type)
{
	switch (type) {
	case GS_BLEND_ZERO:        return GL_ZERO;
	case GS_BLEND_ONE:         return GL_ONE;
	case GS_BLEND_SRCCOLOR:    return GL_SRC_COLOR;
	case GS_BLEND_INVSRCCOLOR: return GL_ONE_MINUS_SRC_COLOR;
	case GS_BLEND_SRCALPHA:    return GL_SRC_ALPHA;
	case GS_BLEND_INVSRCALPHA: return GL_ONE_MINUS_SRC_ALPHA;
	case GS_BLEND_DSTCOLOR:    return GL_DST_COLOR;
	case GS_BLEND_INVDSTCOLOR: return GL_ONE_MINUS_DST_COLOR;
	case GS_BLEND_DSTALPHA:    return GL_DST_ALPHA;
	case GS_BLEND_INVDSTALPHA: return GL_ONE_MINUS_DST_ALPHA;
	case GS_BLEND_SRCALPHASAT: return GL_SRC_ALPHA_SATURATE;
	}

	return GL_ONE;
}