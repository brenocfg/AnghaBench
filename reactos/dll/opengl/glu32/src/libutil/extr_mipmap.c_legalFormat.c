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
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
#define  GL_ALPHA 140 
#define  GL_BGR 139 
#define  GL_BGRA 138 
#define  GL_BLUE 137 
#define  GL_COLOR_INDEX 136 
#define  GL_DEPTH_COMPONENT 135 
 int /*<<< orphan*/  GL_FALSE ; 
#define  GL_GREEN 134 
#define  GL_LUMINANCE 133 
#define  GL_LUMINANCE_ALPHA 132 
#define  GL_RED 131 
#define  GL_RGB 130 
#define  GL_RGBA 129 
#define  GL_STENCIL_INDEX 128 
 int /*<<< orphan*/  GL_TRUE ; 

__attribute__((used)) static GLboolean legalFormat(GLenum format)
{
    switch(format) {
      case GL_COLOR_INDEX:
      case GL_STENCIL_INDEX:
      case GL_DEPTH_COMPONENT:
      case GL_RED:
      case GL_GREEN:
      case GL_BLUE:
      case GL_ALPHA:
      case GL_RGB:
      case GL_RGBA:
      case GL_LUMINANCE:
      case GL_LUMINANCE_ALPHA:
      case GL_BGR:
      case GL_BGRA:
	return GL_TRUE;
      default:
	return GL_FALSE;
    }
}