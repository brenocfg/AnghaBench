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
struct gl_image {int dummy; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLint ;
typedef  scalar_t__ GLenum ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 scalar_t__ GL_BITMAP ; 
 scalar_t__ GL_COLOR_INDEX ; 
 scalar_t__ GL_DEPTH_COMPONENT ; 
 scalar_t__ GL_STENCIL_INDEX ; 
 scalar_t__ gl_sizeof_type (scalar_t__) ; 
 struct gl_image* gl_unpack_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/  const*) ; 

struct gl_image *
gl_unpack_texsubimage( GLcontext *ctx, GLint width, GLint height,
                       GLenum format, GLenum type, const GLvoid *pixels )
{
   if (type==GL_BITMAP && format!=GL_COLOR_INDEX) {
      return NULL;
   }

   if (format==GL_STENCIL_INDEX || format==GL_DEPTH_COMPONENT){
      return NULL;
   }

   if (gl_sizeof_type(type)<=0) {
      return NULL;
   }

   return gl_unpack_image( ctx, width, height, format, type, pixels );
}