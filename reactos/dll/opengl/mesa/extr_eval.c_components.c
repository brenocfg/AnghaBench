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
typedef  int GLenum ;

/* Variables and functions */
#define  GL_MAP1_COLOR_4 145 
#define  GL_MAP1_INDEX 144 
#define  GL_MAP1_NORMAL 143 
#define  GL_MAP1_TEXTURE_COORD_1 142 
#define  GL_MAP1_TEXTURE_COORD_2 141 
#define  GL_MAP1_TEXTURE_COORD_3 140 
#define  GL_MAP1_TEXTURE_COORD_4 139 
#define  GL_MAP1_VERTEX_3 138 
#define  GL_MAP1_VERTEX_4 137 
#define  GL_MAP2_COLOR_4 136 
#define  GL_MAP2_INDEX 135 
#define  GL_MAP2_NORMAL 134 
#define  GL_MAP2_TEXTURE_COORD_1 133 
#define  GL_MAP2_TEXTURE_COORD_2 132 
#define  GL_MAP2_TEXTURE_COORD_3 131 
#define  GL_MAP2_TEXTURE_COORD_4 130 
#define  GL_MAP2_VERTEX_3 129 
#define  GL_MAP2_VERTEX_4 128 

__attribute__((used)) static GLint components( GLenum target )
{
   switch (target) {
      case GL_MAP1_VERTEX_3:		return 3;
      case GL_MAP1_VERTEX_4:		return 4;
      case GL_MAP1_INDEX:		return 1;
      case GL_MAP1_COLOR_4:		return 4;
      case GL_MAP1_NORMAL:		return 3;
      case GL_MAP1_TEXTURE_COORD_1:	return 1;
      case GL_MAP1_TEXTURE_COORD_2:	return 2;
      case GL_MAP1_TEXTURE_COORD_3:	return 3;
      case GL_MAP1_TEXTURE_COORD_4:	return 4;
      case GL_MAP2_VERTEX_3:		return 3;
      case GL_MAP2_VERTEX_4:		return 4;
      case GL_MAP2_INDEX:		return 1;
      case GL_MAP2_COLOR_4:		return 4;
      case GL_MAP2_NORMAL:		return 3;
      case GL_MAP2_TEXTURE_COORD_1:	return 1;
      case GL_MAP2_TEXTURE_COORD_2:	return 2;
      case GL_MAP2_TEXTURE_COORD_3:	return 3;
      case GL_MAP2_TEXTURE_COORD_4:	return 4;
      default:				return 0;
   }
}