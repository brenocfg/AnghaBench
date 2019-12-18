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
typedef  enum wined3d_primitive_type { ____Placeholder_wined3d_primitive_type } wined3d_primitive_type ;
typedef  int GLenum ;

/* Variables and functions */
#define  GL_LINES 137 
#define  GL_LINES_ADJACENCY 136 
#define  GL_LINE_STRIP 135 
#define  GL_LINE_STRIP_ADJACENCY 134 
#define  GL_POINTS 133 
#define  GL_TRIANGLES 132 
#define  GL_TRIANGLES_ADJACENCY 131 
#define  GL_TRIANGLE_FAN 130 
#define  GL_TRIANGLE_STRIP 129 
#define  GL_TRIANGLE_STRIP_ADJACENCY 128 
 int gl_primitive_type_from_d3d (int) ; 

__attribute__((used)) static GLenum gl_tfb_primitive_type_from_d3d(enum wined3d_primitive_type primitive_type)
{
    GLenum gl_primitive_type = gl_primitive_type_from_d3d(primitive_type);
    switch (gl_primitive_type)
    {
        case GL_POINTS:
            return GL_POINTS;

        case GL_LINE_STRIP:
        case GL_LINE_STRIP_ADJACENCY:
        case GL_LINES_ADJACENCY:
        case GL_LINES:
            return GL_LINES;

        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_STRIP_ADJACENCY:
        case GL_TRIANGLES_ADJACENCY:
        case GL_TRIANGLES:
            return GL_TRIANGLES;

        default:
            return gl_primitive_type;
    }
}