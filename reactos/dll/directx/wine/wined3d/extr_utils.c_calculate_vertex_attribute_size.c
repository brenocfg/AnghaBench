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
typedef  int /*<<< orphan*/  GLushort ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLhalfNV ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  int /*<<< orphan*/  GLbyte ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  GL_BYTE 136 
#define  GL_FLOAT 135 
#define  GL_HALF_FLOAT 134 
#define  GL_INT 133 
#define  GL_SHORT 132 
#define  GL_UNSIGNED_BYTE 131 
#define  GL_UNSIGNED_INT 130 
#define  GL_UNSIGNED_INT_2_10_10_10_REV 129 
#define  GL_UNSIGNED_SHORT 128 

__attribute__((used)) static unsigned int calculate_vertex_attribute_size(GLenum type, unsigned int component_count)
{
    switch (type)
    {
        case GL_HALF_FLOAT:
            return component_count * sizeof(GLhalfNV);
        case GL_FLOAT:
            return component_count * sizeof(GLfloat);
        case GL_BYTE:
            return component_count * sizeof(GLbyte);
        case GL_UNSIGNED_BYTE:
            return component_count * sizeof(GLubyte);
        case GL_SHORT:
            return component_count * sizeof(GLshort);
        case GL_UNSIGNED_SHORT:
            return component_count * sizeof(GLushort);
        case GL_INT:
            return component_count * sizeof(GLint);
        case GL_UNSIGNED_INT:
            return component_count * sizeof(GLuint);
        case GL_UNSIGNED_INT_2_10_10_10_REV:
            return sizeof(GLuint);
        default:
            FIXME("Unhandled GL type %#x.\n", type);
            return 0;
    }
}