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
typedef  enum gs_draw_mode { ____Placeholder_gs_draw_mode } gs_draw_mode ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_LINES ; 
 int /*<<< orphan*/  GL_LINE_STRIP ; 
 int /*<<< orphan*/  GL_POINTS ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
#define  GS_LINES 132 
#define  GS_LINESTRIP 131 
#define  GS_POINTS 130 
#define  GS_TRIS 129 
#define  GS_TRISTRIP 128 

__attribute__((used)) static inline GLenum convert_gs_topology(enum gs_draw_mode mode)
{
	switch (mode) {
	case GS_POINTS:    return GL_POINTS;
	case GS_LINES:     return GL_LINES;
	case GS_LINESTRIP: return GL_LINE_STRIP;
	case GS_TRIS:      return GL_TRIANGLES;
	case GS_TRISTRIP:  return GL_TRIANGLE_STRIP;
	}

	return GL_POINTS;
}