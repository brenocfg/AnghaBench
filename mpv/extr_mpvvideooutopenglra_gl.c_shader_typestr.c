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
typedef  int GLenum ;

/* Variables and functions */
#define  GL_COMPUTE_SHADER 130 
#define  GL_FRAGMENT_SHADER 129 
#define  GL_VERTEX_SHADER 128 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static const char *shader_typestr(GLenum type)
{
    switch (type) {
    case GL_VERTEX_SHADER:   return "vertex";
    case GL_FRAGMENT_SHADER: return "fragment";
    case GL_COMPUTE_SHADER:  return "compute";
    default: abort();
    }
}