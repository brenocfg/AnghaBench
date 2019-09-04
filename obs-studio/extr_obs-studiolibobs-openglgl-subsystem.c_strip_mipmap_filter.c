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
typedef  int GLint ;

/* Variables and functions */
#define  GL_LINEAR 133 
#define  GL_LINEAR_MIPMAP_LINEAR 132 
#define  GL_LINEAR_MIPMAP_NEAREST 131 
#define  GL_NEAREST 130 
#define  GL_NEAREST_MIPMAP_LINEAR 129 
#define  GL_NEAREST_MIPMAP_NEAREST 128 

__attribute__((used)) static void strip_mipmap_filter(GLint *filter)
{
	switch (*filter) {
		case GL_NEAREST:
		case GL_LINEAR:
			return;
		case GL_NEAREST_MIPMAP_NEAREST:
		case GL_NEAREST_MIPMAP_LINEAR:
			*filter = GL_NEAREST;
			return;
		case GL_LINEAR_MIPMAP_NEAREST:
		case GL_LINEAR_MIPMAP_LINEAR:
			*filter = GL_LINEAR;
			return;
	}
	*filter = GL_NEAREST;
}